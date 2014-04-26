//////////////////////////////////////////////////////////////////////////
//  Class Name: DuiImgPool
// Description: Image Pool
//     Creator: Huang jianxiong
//     Version: 2012.8.30 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <dui/duistd.h>
#include <dui/duiobject.h>
#include <dui/duiimgpool.h>
#include <dui/duiresprovider.h>
#include <dui/DuiSystem.h>

namespace DuiEngine
{

template<> DuiImgPool * Singleton<DuiImgPool>::ms_Singleton =0;

DuiImgPool::DuiImgPool()
{
    m_pFunOnKeyRemoved=OnImageRemoved;
}

DuiImgPool::~DuiImgPool()
{
    RemoveAll();//��Ҫ������ͼƬ�����ͷ�gdi+����������ͷ��ڴ�ʱ�������
}

CDuiImgBase * DuiImgPool::GetImage(LPCTSTR pszImgName,LPCTSTR pszType)
{
    DuiResID resid(pszType,pszImgName);
    if(HasKey(resid))
    {
        return GetKeyObject(resid);
    }
    else
    {
        DuiResProviderBase * pResProvider=DuiSystem::getSingleton().GetResProvider();
        DUIASSERT(pResProvider);
        CDuiImgBase *pImg=NULL;
        if(pszType)
        {
            pImg=pResProvider->LoadImage(pszType,pszImgName);
        }
        else
        {
            //ö������֧�ֵ�ͼƬ��Դ�����Զ�ƥ��
            CDuiImgDecoder *pImgDecoder=pResProvider->GetImageDecoder();
            DUIASSERT(pImgDecoder);
            LPCTSTR pszTypes=pImgDecoder->GetSupportTypes();
            while(*pszTypes)
            {
                if(pResProvider->HasResource(pszTypes,pszImgName))
                {
                    pImg=pResProvider->LoadImage(pszTypes,pszImgName);
                    if(pImg) break;
                }
                pszTypes+=_tcslen(pszTypes)+1;
            }
        }
        if(pImg)
        {
            AddKeyObject(resid,pImg);
            if(pszType!=NULL)
			{
				pImg->AddRef();
				AddKeyObject(DuiResID(NULL,pszImgName),pImg);//nameΨһʱ��֤��ʹ������Ҳ���ҵ���ͼƬ��Դ
			}
        }
        return pImg;
    }
}

}//namespace DuiEngine