#include "Select.h"

void Select::SetMatrix(TMatrix* pWorld, TMatrix* pView, TMatrix* pProj)
{
	
		if (pWorld != NULL)
		{
			m_matWorld = *pWorld;
			m_vCenter.x = pWorld->_41;
			m_vCenter.y = pWorld->_42;
			m_vCenter.z = pWorld->_43;
		}
		if (pView != NULL)
		{
			m_matView = *pView;
		}
		if (pProj != NULL)
		{
			m_matProj = *pProj;
		}
		Update();
	
}
void Select::Update()
{
	// Get the pick ray from the mouse position
	//if (I_Input.m_DIMouseState.rgbButtons[0])
	{
		POINT ptCursor;
		GetCursorPos(&ptCursor);
		ScreenToClient(g_hWnd, &ptCursor);

		// Compute the vector of the pick ray in screen space
		TVector3 v;
		// ��� 1
		/*v.x =  ( ( ( 2.0f * ptCursor.x ) / TBASIS::g_iClientWidth  ) - 1 );
		v.y = -( ( ( 2.0f * ptCursor.y ) / TBASIS::g_iClientHeight ) - 1 );
		v.z =  1.0f;
		D3DXVec3TransformCoord( &v, &v, &m );*/
		// ��� 2
		v.x = (((2.0f * ptCursor.x) / gWindow_Width) - 1) / m_matProj._11;
		v.y = -(((2.0f * ptCursor.y) / gWindow_Height) - 1) / m_matProj._22;
		v.z = 1.0f;

		// Get the inverse view matrix
		// ���尡 ��ȯ�Ǿ��ٸ� ���ؽ����۵� ���ؾ� �Ѵ�. �׷��� ��ŷ���ؽ��� ��������� �������� ����
		// ���ؽ�����(��Į��ǥ)���� ���� ����ϱ� ������ ������ ��ǥ�� �ٸ��� �ȴ�. 
		// �ᱹ ���ؽ������� ������ ��ķ� ���ؼ� ������ ����ϰų�( ����ĸ� �ι����Ѵ�. )
		// ������ ��ȯ�ؾ߸� �ȴ�.( ����ĵ� �ι��� �ؾ��Ѵ�.)
		// ���⼭�� ������ ��ȯ�Ͽ� ������ ��ǥ��� ó���ϰ� �ִ�.
		// Ư���� ��찡 �ƴ϶�� ������ĸ� ������ķ� ����ض�.
		TMatrix mWorldView = m_matWorld * m_matView;
		TMatrix m;
		D3DXMatrixInverse(&m, NULL, &mWorldView);

		// ��� 1
		m_Ray.vOrigin = TVector3(0.0f, 0.0f, 0.0f);
		m_Ray.vDirection = TVector3(v.x, v.y, v.z);
		D3DXVec3TransformCoord(&m_Ray.vOrigin, &m_Ray.vOrigin, &m);
		D3DXVec3TransformNormal(&m_Ray.vDirection, &m_Ray.vDirection, &m);
		D3DXVec3Normalize(&m_Ray.vDirection, &m_Ray.vDirection);

		// ��� 2		
		//m_Ray.vDirection.x = v.x*m._11 + v.y*m._21 + v.z*m._31;
		//m_Ray.vDirection.y = v.x*m._12 + v.y*m._22 + v.z*m._32;
		//m_Ray.vDirection.z = v.x*m._13 + v.y*m._23 + v.z*m._33;
		//D3DXVec3Normalize(&m_Ray.vDirection, &m_Ray.vDirection);
		//m_Ray.vOrigin.x = m._41;
		//m_Ray.vOrigin.y = m._42;
		//m_Ray.vOrigin.z = m._43;
	}
}


bool Select::ChkPick(TVector3& v0, TVector3& v1, TVector3& v2)
{
	FLOAT fBary1, fBary2;
	FLOAT fDist;
	// Check if the pick ray passes through this point
	if (IntersectTriangle(m_Ray.vOrigin, m_Ray.vDirection, v0, v1, v2,
		&fDist, &fBary1, &fBary2))
	{
		m_vSrcVex[0] = v0;
		m_vSrcVex[1] = v1;
		m_vSrcVex[2] = v2;
		m_matWorldPick = m_matWorld;
		return true;
	}

	return false;
}
bool Select::IntersectTriangle(const TVector3& orig, const TVector3& dir,
	TVector3& v0, TVector3& v1, TVector3& v2,
	FLOAT* t, FLOAT* u, FLOAT* v)
{
	// Find vectors for two edges sharing vert0
	TVector3 edge1 = v1 - v0;
	TVector3 edge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	//TVector3 pvec;
	D3DXVec3Cross(&pvec, &dir, &edge2);

	// If determinant is near zero, ray lies in plane of triangle
	FLOAT det = D3DXVec3Dot(&edge1, &pvec);

	//TVector3 tvec; // ������ ����� �� �� �ֵ��� det ������ �����´�.
	if (det > 0)
	{
		tvec = orig - v0;
	}
	else
	{
		tvec = v0 - orig;
		det = -det;
	}

	if (det < 0.0001f)
		return false;

	// Calculate U parameter and test bounds
	*u = D3DXVec3Dot(&tvec, &pvec);
	if (*u < 0.0f || *u > det)
		return false;

	// Prepare to test V parameter
	//TVector3 qvec;
	D3DXVec3Cross(&qvec, &tvec, &edge1);

	// Calculate V parameter and test bounds
	*v = D3DXVec3Dot(&dir, &qvec);
	if (*v < 0.0f || *u + *v > det)
		return false;

	// Calculate t, scale parameters, ray intersects triangle
	*t = D3DXVec3Dot(&edge2, &qvec);
	FLOAT fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;

	//TVector3 e3 = v2 - v1;
	//TVector3 vi = orig + (*t) * dir;
	//TVector3 i0 = v0 + edge1 * (*u) + edge2 * (*v);
	//
	//this->vPickRayOrig = orig;
	//this->vPickRayDir = dir;
	return true;
}