// 2013 Hiroyuki Ogasawara
// vim:ts=4 sw=4 noet:

#include	"CoreLib.h"
#include	"Matrix4.h"


namespace flatlib {
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

namespace math {
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



alignas(32) Matrix4	Matrix4::_Identity= Matrix4(
                            1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f );



void Matrix4::MulCopy_4_4_FPU( const Matrix4& m0, const Matrix4& m1 )
{
	Matrix4	t;
	t._11= m1._11*m0._11 + m1._12*m0._21 + m1._13*m0._31 + m1._14*m0._41;
	t._12= m1._11*m0._12 + m1._12*m0._22 + m1._13*m0._32 + m1._14*m0._42;
	t._13= m1._11*m0._13 + m1._12*m0._23 + m1._13*m0._33 + m1._14*m0._43;
	t._14= m1._11*m0._14 + m1._12*m0._24 + m1._13*m0._34 + m1._14*m0._44;
	t._21= m1._21*m0._11 + m1._22*m0._21 + m1._23*m0._31 + m1._24*m0._41;
	t._22= m1._21*m0._12 + m1._22*m0._22 + m1._23*m0._32 + m1._24*m0._42;
	t._23= m1._21*m0._13 + m1._22*m0._23 + m1._23*m0._33 + m1._24*m0._43;
	t._24= m1._21*m0._14 + m1._22*m0._24 + m1._23*m0._34 + m1._24*m0._44;
	t._31= m1._31*m0._11 + m1._32*m0._21 + m1._33*m0._31 + m1._34*m0._41;
	t._32= m1._31*m0._12 + m1._32*m0._22 + m1._33*m0._32 + m1._34*m0._42;
	t._33= m1._31*m0._13 + m1._32*m0._23 + m1._33*m0._33 + m1._34*m0._43;
	t._34= m1._31*m0._14 + m1._32*m0._24 + m1._33*m0._34 + m1._34*m0._44;
	t._41= m1._41*m0._11 + m1._42*m0._21 + m1._43*m0._31 + m1._44*m0._41;
	t._42= m1._41*m0._12 + m1._42*m0._22 + m1._43*m0._32 + m1._44*m0._42;
	t._43= m1._41*m0._13 + m1._42*m0._23 + m1._43*m0._33 + m1._44*m0._43;
	t._44= m1._41*m0._14 + m1._42*m0._24 + m1._43*m0._34 + m1._44*m0._44;
	Copy( t );
}





void  Matrix4::RotationX_CS( float cs, float ss )
{
	float	x[4];
	x[0]   = _21 * cs + _31 * ss;
	x[1]   = _22 * cs + _32 * ss;
	x[2]   = _23 * cs + _33 * ss;
	x[3]   = _24 * cs + _34 * ss;
	_31= _21 *-ss + _31 * cs;
	_32= _22 *-ss + _32 * cs;
	_33= _23 *-ss + _33 * cs;
	_34= _24 *-ss + _34 * cs;
	_21= x[0];
	_22= x[1];
	_23= x[2];
	_24= x[3];
}




void  Matrix4::RotationY_CS( float cs, float ss )
{
	float	x[4];
	x[0]   = _11 * cs + _31 *-ss;
	x[1]   = _12 * cs + _32 *-ss;
	x[2]   = _13 * cs + _33 *-ss;
	x[3]   = _14 * cs + _34 *-ss;
	_31= _11 * ss + _31 * cs;
	_32= _12 * ss + _32 * cs;
	_33= _13 * ss + _33 * cs;
	_34= _14 * ss + _34 * cs;
	_11= x[0];
	_12= x[1];
	_13= x[2];
	_14= x[3];
}




void  Matrix4::RotationZ_CS( float cs, float ss )
{
	float	x[4];
	x[0]   = _11 * cs + _21 * ss;
	x[1]   = _12 * cs + _22 * ss;
	x[2]   = _13 * cs + _23 * ss;
	x[3]   = _14 * cs + _24 * ss;
	_21= _11 *-ss + _21 * cs;
	_22= _12 *-ss + _22 * cs;
	_23= _13 *-ss + _23 * cs;
	_24= _14 *-ss + _24 * cs;
	_11= x[0];
	_12= x[1];
	_13= x[2];
	_14= x[3];
}





void Matrix4::TransposeCopy_FPU( const Matrix4& mat0 )
{
	FL_ASSERT( this != &mat0 );

	_11= mat0._11;
	_21= mat0._12;
	_31= mat0._13;
	_41= mat0._14;
	_12= mat0._21;
	_22= mat0._22;
	_32= mat0._23;
	_42= mat0._24;
	_13= mat0._31;
	_23= mat0._32;
	_33= mat0._33;
	_43= mat0._34;
	_14= mat0._41;
	_24= mat0._42;
	_34= mat0._43;
	_44= mat0._44;
}



void Matrix4::Dump( const char* msg ) const
{
#if !FL_RETAIL
    if( !msg ){
        msg= "";
    }
	FL_PRINT( "%s_a %f %f %f %f\n", msg, _11, _21, _31, _41 );
	FL_PRINT( "%s_b %f %f %f %f\n", msg, _12, _22, _32, _42 );
	FL_PRINT( "%s_c %f %f %f %f\n", msg, _13, _23, _33, _43 );
	FL_PRINT( "%s_d %f %f %f %f\n", msg, _14, _24, _34, _44 );
#endif
}



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
}


