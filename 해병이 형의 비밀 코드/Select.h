#pragma once
#include"CDefine.h"

struct RAY
{
	float			fExtent;
	TVector3		vOrigin;
	TVector3		vDirection;
	RAY()
	{
		//  fExtent > 0 : ���׸�Ʈ�� ��� 
		fExtent = -1;
	}
};
class Select
{
public:
	RAY		    m_Ray;
	TVector3	m_vIntersection;
	TMatrix		m_matWorld;
	TMatrix		m_matView;
	TMatrix		m_matProj;
	TVector3	m_vDxR;
	TVector3	m_vCenter;
	TVector3	m_vSrcVex[3];
	float		m_fPickDistance;
	TMatrix		m_matWorldPick;
	TVector3	qvec;
	TVector3	tvec;
	TVector3	pvec;

public:
	void SetMatrix(TMatrix* pWorld, TMatrix* pView, TMatrix* pProj);
	void Update();
	bool ChkPick(TVector3& v0, TVector3& v1, TVector3& v2);
	bool IntersectTriangle(const TVector3& orig, const TVector3& dir,
						   TVector3& v0, TVector3& v1, TVector3& v2,
						   FLOAT* t, FLOAT* u, FLOAT* v);
};

