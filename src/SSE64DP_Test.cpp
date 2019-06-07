// 2014 Hiroyuki Ogasawara
// vim:ts=4 sw=4 noet:

#include	<minilib/CoreLib.h>
#include	<minilib/SystemInfo.h>
#include	"TimerClass.h"
#include	"SSE64DP_Test.h"


//-----------------------------------------------------------------------------
#if flCPU_X64
//-----------------------------------------------------------------------------

namespace SSE64DP {
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

using namespace flatlib;

/*
	xmm0-xmm7
*/



typedef	uint64_t	CounterType;


//=============================================================================
// SSE
//=============================================================================

static void check_result( double ret, double ans )
{
	FL_LOG( "check: %f %f\n", ret, ans );
	flASSERT( ret == ans );
}


#define SSE_REG_CLEAR() \
		"xorpd	%%xmm0, %%xmm0\n"	\
		"xorpd	%%xmm1, %%xmm1\n"	\
		"xorpd	%%xmm2, %%xmm2\n"	\
		"xorpd	%%xmm3, %%xmm3\n"	\
		"xorpd	%%xmm4, %%xmm4\n"	\
		"xorpd	%%xmm5, %%xmm5\n"	\
		"xorpd	%%xmm6, %%xmm6\n"	\
		"xorpd	%%xmm7, %%xmm7\n"	\
		"xorpd	%%xmm8, %%xmm8\n"	\
		"xorpd	%%xmm9, %%xmm9\n"	\
		"xorpd	%%xmm10, %%xmm10\n"	\
		"xorpd	%%xmm11, %%xmm11\n"	\
		"xorpd	%%xmm12, %%xmm12\n"	\
		"xorpd	%%xmm13, %%xmm13\n"	\
		"xorpd	%%xmm14, %%xmm14\n"	\
		"xorpd	%%xmm15, %%xmm15\n"	\





//-----------------------------------------------------------------------------
// Single Interleave 8
//-----------------------------------------------------------------------------

#define SSE_S_IR8_8(op) \
			op " %%xmm0, %%xmm0\n"		\
			op " %%xmm1, %%xmm1\n"		\
			op " %%xmm2, %%xmm2\n"		\
			op " %%xmm3, %%xmm3\n"		\
			op " %%xmm4, %%xmm4\n"		\
			op " %%xmm5, %%xmm5\n"		\
			op " %%xmm6, %%xmm6\n"		\
			op " %%xmm7, %%xmm7\n"



#define SSE_S_IR8_0(op,name) \
static uint64_t SSE_S_IR8_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3, ret4, ret5, ret6, ret7;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		SSE_REG_CLEAR()			\
		"mov		$1, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm0\n"	\
		"shufpd		$0, %%xmm0, %%xmm0\n"	\
		"movapd		%%xmm0, %%xmm2\n"	\
		"movapd		%%xmm0, %%xmm4\n"	\
		"movapd		%%xmm0, %%xmm6\n"	\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm1\n"	\
		"shufpd		$0, %%xmm1, %%xmm1\n"	\
		"movapd		%%xmm1, %%xmm3\n"	\
		"movapd		%%xmm1, %%xmm5\n"	\
		"movapd		%%xmm1, %%xmm7\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		SSE_S_IR8_8( op )	\
		SSE_S_IR8_8( op )	\
		SSE_S_IR8_8( op )	\
		SSE_S_IR8_8( op )	\
		SSE_S_IR8_8( op )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
		"movsd	%%xmm4, %[o4]\n"	\
		"movsd	%%xmm5, %[o5]\n"	\
		"movsd	%%xmm6, %[o6]\n"	\
		"movsd	%%xmm7, %[o7]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3),	\
		[o4]"=m"(ret4),	\
		[o5]"=m"(ret5),	\
		[o6]"=m"(ret6),	\
		[o7]"=m"(ret7)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
		); \
\
	timer.End();		\
	timer.Dump( op );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );	\
	check_result( ret4, answer );	\
	check_result( ret5, answer );	\
	check_result( ret6, answer );	\
	check_result( ret7, answer );*/	\
	return	timer.Result();	\
}

#define SSE_S_IR8(op,name) SSE_S_IR8_0(#op,name)











//-----------------------------------------------------------------------------
// Single Interleave src 4
//-----------------------------------------------------------------------------

#define SSE_S_IRS4_8(op) \
			op " %%xmm0, %%xmm4\n"		\
			op " %%xmm1, %%xmm5\n"		\
			op " %%xmm2, %%xmm6\n"		\
			op " %%xmm3, %%xmm7\n"		\
			op " %%xmm4, %%xmm0\n"		\
			op " %%xmm5, %%xmm1\n"		\
			op " %%xmm6, %%xmm2\n"		\
			op " %%xmm7, %%xmm3\n"



#define SSE_S_IRS4_0(op,name) \
static uint64_t SSE_S_IRS4_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3, ret4, ret5, ret6, ret7;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		SSE_REG_CLEAR()			\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm0\n"	\
		"shufpd		$0, %%xmm0, %%xmm0\n"	\
		"movapd		%%xmm0, %%xmm2\n"	\
		"movapd		%%xmm0, %%xmm4\n"	\
		"movapd		%%xmm0, %%xmm6\n"	\
		"mov		$5, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm1\n"	\
		"shufpd		$0, %%xmm1, %%xmm1\n"	\
		"movapd		%%xmm1, %%xmm3\n"	\
		"movapd		%%xmm1, %%xmm5\n"	\
		"movapd		%%xmm1, %%xmm7\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		SSE_S_IRS4_8( op )	\
		SSE_S_IRS4_8( op )	\
		SSE_S_IRS4_8( op )	\
		SSE_S_IRS4_8( op )	\
		SSE_S_IRS4_8( op )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
		"movsd	%%xmm4, %[o4]\n"	\
		"movsd	%%xmm5, %[o5]\n"	\
		"movsd	%%xmm6, %[o6]\n"	\
		"movsd	%%xmm7, %[o7]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3),	\
		[o4]"=m"(ret4),	\
		[o5]"=m"(ret5),	\
		[o6]"=m"(ret6),	\
		[o7]"=m"(ret7)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
	);\
	timer.End();		\
	timer.Dump( op );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );	\
	check_result( ret4, answer );	\
	check_result( ret5, answer );	\
	check_result( ret6, answer );	\
	check_result( ret7, answer );*/	\
	return	timer.Result();	\
}

#define SSE_S_IRS4(op,name) SSE_S_IRS4_0(#op,name)

























//-----------------------------------------------------------------------------
// Single Interleave 8 MAD
//-----------------------------------------------------------------------------

#define SSE_M_IR8_8(op1,op2) \
			op1 " %%xmm0, %%xmm0\n"		\
			op2 " %%xmm1, %%xmm1\n"		\
			op1 " %%xmm2, %%xmm2\n"		\
			op2 " %%xmm3, %%xmm3\n"		\
			op1 " %%xmm4, %%xmm4\n"		\
			op2 " %%xmm5, %%xmm5\n"		\
			op1 " %%xmm6, %%xmm6\n"		\
			op2 " %%xmm7, %%xmm7\n"



#define SSE_M_IR8_0(op1,op2,name) \
static uint64_t SSE_M_IR8_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3, ret4, ret5, ret6, ret7;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		SSE_REG_CLEAR()			\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm0\n"	\
		"shufpd		$0, %%xmm0, %%xmm0\n"	\
		"movapd		%%xmm0, %%xmm2\n"	\
		"movapd		%%xmm0, %%xmm4\n"	\
		"movapd		%%xmm0, %%xmm6\n"	\
		"mov		$5, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm1\n"	\
		"shufpd		$0, %%xmm1, %%xmm1\n"	\
		"movapd		%%xmm1, %%xmm3\n"	\
		"movapd		%%xmm1, %%xmm5\n"	\
		"movapd		%%xmm1, %%xmm7\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		SSE_M_IR8_8( op1,op2 )	\
		SSE_M_IR8_8( op1,op2 )	\
		SSE_M_IR8_8( op1,op2 )	\
		SSE_M_IR8_8( op1,op2 )	\
		SSE_M_IR8_8( op1,op2 )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
		"movsd	%%xmm4, %[o4]\n"	\
		"movsd	%%xmm5, %[o5]\n"	\
		"movsd	%%xmm6, %[o6]\n"	\
		"movsd	%%xmm7, %[o7]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3),	\
		[o4]"=m"(ret4),	\
		[o5]"=m"(ret5),	\
		[o6]"=m"(ret6),	\
		[o7]"=m"(ret7)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
	);\
	timer.End();		\
	timer.Dump( op1 );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );	\
	check_result( ret4, answer );	\
	check_result( ret5, answer );	\
	check_result( ret6, answer );	\
	check_result( ret7, answer );*/	\
	return	timer.Result();	\
}

#define SSE_M_IR8(op1,op2,name) SSE_M_IR8_0(#op1,#op2,name)










//-----------------------------------------------------------------------------
// Single Interleave 9 MAD op3
//-----------------------------------------------------------------------------

#define SSE_M_IR9_9(op1,op2,op3) \
			op1 " %%xmm0, %%xmm0\n"		\
			op2 " %%xmm1, %%xmm1\n"		\
			op3 " %%xmm2, %%xmm2\n"		\
			op1 " %%xmm3, %%xmm3\n"		\
			op2 " %%xmm4, %%xmm4\n"		\
			op3 " %%xmm5, %%xmm5\n"		\
			op1 " %%xmm6, %%xmm6\n"		\
			op2 " %%xmm7, %%xmm7\n"		\
			op3 " %%xmm8, %%xmm8\n"



#define SSE_M_IR9_0(op1,op2,op3,name) \
static uint64_t SSE_M_IR9_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3, ret4, ret5, ret6, ret7;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		SSE_REG_CLEAR()			\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm0\n"	\
		"shufpd		$0, %%xmm0, %%xmm0\n"	\
		"movapd		%%xmm0, %%xmm2\n"	\
		"movapd		%%xmm0, %%xmm4\n"	\
		"movapd		%%xmm0, %%xmm6\n"	\
		"mov		$5, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm1\n"	\
		"shufpd		$0, %%xmm1, %%xmm1\n"	\
		"movapd		%%xmm1, %%xmm3\n"	\
		"movapd		%%xmm1, %%xmm5\n"	\
		"movapd		%%xmm1, %%xmm7\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		SSE_M_IR9_9( op1,op2,op3 )	\
		SSE_M_IR9_9( op1,op2,op3 )	\
		SSE_M_IR9_9( op1,op2,op3 )	\
		SSE_M_IR9_9( op1,op2,op3 )	\
		SSE_M_IR9_9( op1,op2,op3 )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
		"movsd	%%xmm4, %[o4]\n"	\
		"movsd	%%xmm5, %[o5]\n"	\
		"movsd	%%xmm6, %[o6]\n"	\
		"movsd	%%xmm7, %[o7]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3),	\
		[o4]"=m"(ret4),	\
		[o5]"=m"(ret5),	\
		[o6]"=m"(ret6),	\
		[o7]"=m"(ret7)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
	);\
	timer.End();		\
	timer.Dump( op1 );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );	\
	check_result( ret4, answer );	\
	check_result( ret5, answer );	\
	check_result( ret6, answer );	\
	check_result( ret7, answer );*/	\
	return	timer.Result();	\
}

#define SSE_M_IR9(op1,op2,op3,name) SSE_M_IR9_0(#op1,#op2,#op3,name)






//-----------------------------------------------------------------------------
// Single Interleave 8 FMA
//-----------------------------------------------------------------------------

#define SSE_S_FMA_IR8_8(op) \
			op " %%xmm0, %%xmm0, %%xmm0\n"		\
			op " %%xmm1, %%xmm1, %%xmm1\n"		\
			op " %%xmm2, %%xmm2, %%xmm2\n"		\
			op " %%xmm3, %%xmm3, %%xmm3\n"		\
			op " %%xmm4, %%xmm4, %%xmm4\n"		\
			op " %%xmm5, %%xmm5, %%xmm5\n"		\
			op " %%xmm6, %%xmm6, %%xmm6\n"		\
			op " %%xmm7, %%xmm7, %%xmm7\n"



#define SSE_S_FMA_IR8_0(op,name) \
static uint64_t SSE_S_FMA_IR8_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3, ret4, ret5, ret6, ret7;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		SSE_REG_CLEAR()			\
		"mov		$1, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm0\n"	\
		"shufpd		$0, %%xmm0, %%xmm0\n"	\
		"movapd		%%xmm0, %%xmm2\n"	\
		"movapd		%%xmm0, %%xmm4\n"	\
		"movapd		%%xmm0, %%xmm6\n"	\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm1\n"	\
		"shufpd		$0, %%xmm1, %%xmm1\n"	\
		"movapd		%%xmm1, %%xmm3\n"	\
		"movapd		%%xmm1, %%xmm5\n"	\
		"movapd		%%xmm1, %%xmm7\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		SSE_S_FMA_IR8_8( op )	\
		SSE_S_FMA_IR8_8( op )	\
		SSE_S_FMA_IR8_8( op )	\
		SSE_S_FMA_IR8_8( op )	\
		SSE_S_FMA_IR8_8( op )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
		"movsd	%%xmm4, %[o4]\n"	\
		"movsd	%%xmm5, %[o5]\n"	\
		"movsd	%%xmm6, %[o6]\n"	\
		"movsd	%%xmm7, %[o7]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3),	\
		[o4]"=m"(ret4),	\
		[o5]"=m"(ret5),	\
		[o6]"=m"(ret6),	\
		[o7]"=m"(ret7)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
		); \
\
	timer.End();		\
	timer.Dump( op );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );	\
	check_result( ret4, answer );	\
	check_result( ret5, answer );	\
	check_result( ret6, answer );	\
	check_result( ret7, answer );*/	\
	return	timer.Result();	\
}

#define SSE_S_FMA_IR8(op,name) SSE_S_FMA_IR8_0(#op,name)




















//=============================================================================
// AVX
//=============================================================================


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#define AVX_REG_CLEAR() \
		"vxorpd	%%ymm0, %%ymm0, %%ymm0\n"	\
		"vxorpd	%%ymm1, %%ymm1, %%ymm1\n"	\
		"vxorpd	%%ymm2, %%ymm2, %%ymm2\n"	\
		"vxorpd	%%ymm3, %%ymm3, %%ymm3\n"	\
		"vxorpd	%%ymm4, %%ymm4, %%ymm4\n"	\
		"vxorpd	%%ymm5, %%ymm5, %%ymm5\n"	\
		"vxorpd	%%ymm6, %%ymm6, %%ymm6\n"	\
		"vxorpd	%%ymm7, %%ymm7, %%ymm7\n"	\
		"vxorpd	%%ymm8, %%ymm8, %%ymm8\n"	\
		"vxorpd	%%ymm9, %%ymm9, %%ymm9\n"	\
		"vxorpd	%%ymm10, %%ymm10, %%ymm10\n"	\
		"vxorpd	%%ymm11, %%ymm11, %%ymm11\n"	\
		"vxorpd	%%ymm12, %%ymm12, %%ymm12\n"	\
		"vxorpd	%%ymm13, %%ymm13, %%ymm13\n"	\
		"vxorpd	%%ymm14, %%ymm14, %%ymm14\n"	\
		"vxorpd	%%ymm15, %%ymm15, %%ymm15\n"	\



//-----------------------------------------------------------------------------
// Single Interleave 8
//-----------------------------------------------------------------------------

#define AVX_S_IR8_8(op) \
			op " %%ymm9, %%ymm8, %%ymm0\n"		\
			op " %%ymm9, %%ymm8, %%ymm1\n"		\
			op " %%ymm9, %%ymm8, %%ymm2\n"		\
			op " %%ymm9, %%ymm8, %%ymm3\n"		\
			op " %%ymm9, %%ymm8, %%ymm4\n"		\
			op " %%ymm9, %%ymm8, %%ymm5\n"		\
			op " %%ymm9, %%ymm8, %%ymm6\n"		\
			op " %%ymm9, %%ymm8, %%ymm7\n"



#define AVX_S_IR8_0(op,name) \
static uint64_t AVX_S_IR8_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		AVX_REG_CLEAR()			\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm8\n"	\
		"shufpd		$0, %%xmm8, %%xmm8\n"	\
		"vperm2f128	$0, %%ymm8, %%ymm8, %%ymm8\n"	\
		"mov		$5, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm9\n"	\
		"shufpd		$0, %%xmm9, %%xmm9\n"	\
		"vperm2f128	$0, %%ymm9, %%ymm9, %%ymm9\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		AVX_S_IR8_8( op )	\
		AVX_S_IR8_8( op )	\
		AVX_S_IR8_8( op )	\
		AVX_S_IR8_8( op )	\
		AVX_S_IR8_8( op )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
		); \
\
	timer.End();		\
	timer.Dump( op );	\
	check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );	\
	return	timer.Result();	\
}

#define AVX_S_IR8(op,name) AVX_S_IR8_0(#op,name)







//-----------------------------------------------------------------------------
// Single Interleave MAD
//-----------------------------------------------------------------------------

#define AVX_M_IR8_8(op1,op2) \
			op1 " %%ymm9, %%ymm8, %%ymm0\n"		\
			op2 " %%ymm9, %%ymm8, %%ymm1\n"		\
			op1 " %%ymm9, %%ymm8, %%ymm2\n"		\
			op2 " %%ymm9, %%ymm8, %%ymm3\n"		\
			op1 " %%ymm9, %%ymm8, %%ymm4\n"		\
			op2 " %%ymm9, %%ymm8, %%ymm5\n"		\
			op1 " %%ymm9, %%ymm8, %%ymm6\n"		\
			op2 " %%ymm9, %%ymm8, %%ymm7\n"



#define AVX_M_IR8_0(op1,op2,name) \
static uint64_t AVX_M_IR8_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		AVX_REG_CLEAR()			\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm8\n"	\
		"shufpd		$0, %%xmm8, %%xmm8\n"	\
		"vperm2f128	$0, %%ymm8, %%ymm8, %%ymm8\n"	\
		"mov		$5, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm9\n"	\
		"shufpd		$0, %%xmm9, %%xmm9\n"	\
		"vperm2f128	$0, %%ymm9, %%ymm9, %%ymm9\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		AVX_M_IR8_8( op1, op2 )	\
		AVX_M_IR8_8( op1, op2 )	\
		AVX_M_IR8_8( op1, op2 )	\
		AVX_M_IR8_8( op1, op2 )	\
		AVX_M_IR8_8( op1, op2 )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
		); \
\
	timer.End();		\
	timer.Dump( op1 );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );*/	\
	return	timer.Result();	\
}

#define AVX_M_IR8(op1,op2,name) AVX_M_IR8_0(#op1,#op2,name)






//-----------------------------------------------------------------------------
// Single Interleave 9 MAD op3
//-----------------------------------------------------------------------------

#define AVX_M_IR9_9(op1,op2,op3) \
			op1 " %%ymm9, %%ymm8, %%ymm0\n"		\
			op2 " %%ymm9, %%ymm8, %%ymm1\n"		\
			op3 " %%ymm9, %%ymm8, %%ymm2\n"		\
			op1 " %%ymm9, %%ymm8, %%ymm3\n"		\
			op2 " %%ymm9, %%ymm8, %%ymm4\n"		\
			op3 " %%ymm9, %%ymm8, %%ymm5\n"		\
			op1 " %%ymm9, %%ymm8, %%ymm6\n"		\
			op2 " %%ymm9, %%ymm8, %%ymm7\n"		\
			op3 " %%ymm9, %%ymm8, %%ymm10\n"



#define AVX_M_IR9_0(op1,op2,op3,name) \
static uint64_t AVX_M_IR9_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		AVX_REG_CLEAR()			\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm8\n"	\
		"shufpd		$0, %%xmm8, %%xmm8\n"	\
		"vperm2f128	$0, %%ymm8, %%ymm8, %%ymm8\n"	\
		"mov		$5, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm9\n"	\
		"shufpd		$0, %%xmm9, %%xmm9\n"	\
		"vperm2f128	$0, %%ymm9, %%ymm9, %%ymm9\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		AVX_M_IR9_9( op1, op2, op3 )	\
		AVX_M_IR9_9( op1, op2, op3 )	\
		AVX_M_IR9_9( op1, op2, op3 )	\
		AVX_M_IR9_9( op1, op2, op3 )	\
		AVX_M_IR9_9( op1, op2, op3 )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
		); \
\
	timer.End();		\
	timer.Dump( op1 );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );*/	\
	return	timer.Result();	\
}

#define AVX_M_IR9(op1,op2,op3,name) AVX_M_IR9_0(#op1,#op2,#op3,name)





//-----------------------------------------------------------------------------
// Single Interleave 8 FMA
//-----------------------------------------------------------------------------

#define AVX_S_FMA_IR8_8(op) \
			op " %%ymm9, %%ymm8, %%ymm0\n"		\
			op " %%ymm9, %%ymm8, %%ymm1\n"		\
			op " %%ymm9, %%ymm8, %%ymm2\n"		\
			op " %%ymm9, %%ymm8, %%ymm3\n"		\
			op " %%ymm9, %%ymm8, %%ymm4\n"		\
			op " %%ymm9, %%ymm8, %%ymm5\n"		\
			op " %%ymm9, %%ymm8, %%ymm6\n"		\
			op " %%ymm9, %%ymm8, %%ymm7\n"



#define AVX_S_FMA_IR8_0(op,name) \
static uint64_t AVX_S_FMA_IR8_##name( CounterType LoopCount, double answer ) \
{ \
	double	ret0, ret1, ret2, ret3;	\
	TimerClass	timer;			\
	timer.Begin();				\
	__asm__ __volatile__(		\
		AVX_REG_CLEAR()			\
		"mov		$2, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm8\n"	\
		"shufpd		$0, %%xmm8, %%xmm8\n"	\
		"vperm2f128	$0, %%ymm8, %%ymm8, %%ymm8\n"	\
		"mov		$5, %%eax\n"		\
		"cvtsi2sd	%%eax, %%xmm9\n"	\
		"shufpd		$0, %%xmm9, %%xmm9\n"	\
		"vperm2f128	$0, %%ymm9, %%ymm9, %%ymm9\n"	\
		"mov	%[loop], %%rax\n"	\
	"1:\n"	\
		AVX_S_FMA_IR8_8( op )	\
		AVX_S_FMA_IR8_8( op )	\
		AVX_S_FMA_IR8_8( op )	\
		AVX_S_FMA_IR8_8( op )	\
		AVX_S_FMA_IR8_8( op )	\
		"dec	%%rax\n"	\
		"jne	1b\n"	 	\
		"movsd	%%xmm0, %[o0]\n"	\
		"movsd	%%xmm1, %[o1]\n"	\
		"movsd	%%xmm2, %[o2]\n"	\
		"movsd	%%xmm3, %[o3]\n"	\
	:	[o0]"=m"(ret0),	\
		[o1]"=m"(ret1),	\
		[o2]"=m"(ret2),	\
		[o3]"=m"(ret3)	\
	: [loop]"r"(LoopCount)	\
	: "cc","%rax",	\
		"%xmm0","%xmm1","%xmm2","%xmm3","%xmm4","%xmm5","%xmm6","%xmm7",\
		"%xmm8","%xmm9","%xmm10","%xmm11","%xmm12","%xmm13","%xmm14","%xmm15"\
		); \
\
	timer.End();		\
	timer.Dump( op );	\
	/*check_result( ret0, answer );	\
	check_result( ret1, answer );	\
	check_result( ret2, answer );	\
	check_result( ret3, answer );*/	\
	return	timer.Result();	\
}

#define AVX_S_FMA_IR8(op,name) AVX_S_FMA_IR8_0(#op,name)





//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------




static const char*	Instruction_Title[]= {

	"SSE2 mulsd (64bit x1) n8",
	"SSE2 addsd (64bit x1) n8",
	"FMA  vfmaddsd (64bit x1) n8",

	"SSE2 mulpd (64bit x2) n8",
	"SSE2 addpd (64bit x2) n8",
	"SSE2 mul+addpd (64bit x2) n8",
	"FMA  vfmaddsd (64bit x2) n8",

	"SSE2 ml+ad+dpd (64bit x2) n6",

	"SSE2 mulsd (64bit x1) ns4",
	"SSE2 addsd (64bit x1) ns4",

	"SSE2 mulpd (64bit x2) ns4",
	"SSE2 addpd (64bit x2) ns4",

	"AVX vmulpd (64bit x4) n8",
	"AVX vaddpd (64bit x4) n8",
	"AVX vmul+addpd (64bit x4) n8",
	"FMA vfmaddpd (64bit x4) n8",

	"AVX vml_ad_adpd (64bit x4) n6",
};





//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------


FloatTest::FloatTest()
{
	flASSERT( RESULT_MAX <= RESULT_BUFFER_MAX );
	LoopCount= DEFAULT_LOOP;
	ClearResult();


	SetOp( RESULT_SSE_MULSD_IR8,		PER_LOOP_INST * 1, 1	);
	SetOp( RESULT_SSE_ADDSD_IR8,		PER_LOOP_INST * 1, 1	);
	SetOp( RESULT_SSE_FMADDSD_IR8,		PER_LOOP_INST * 2, 2	);

	SetOp( RESULT_SSE_MULPD_IR8,		PER_LOOP_INST * 2, 2	);
	SetOp( RESULT_SSE_ADDPD_IR8,		PER_LOOP_INST * 2, 2	);
	SetOp( RESULT_SSE_MULPD_ADDPD_IR8,	PER_LOOP_INST * 2, 2	);
	SetOp( RESULT_SSE_FMADDPD_IR8,		PER_LOOP_INST * 4, 4	);


	SetOp( RESULT_SSE_ML_AD_ADDPD_IR9,	PER_LOOP_INST_9 * 2, 2	);




	SetOp( RESULT_SSE_MULSD_IRS4,		PER_LOOP_INST * 1, 1	);
	SetOp( RESULT_SSE_ADDSD_IRS4,		PER_LOOP_INST * 1, 1	);

	SetOp( RESULT_SSE_MULPD_IRS4,		PER_LOOP_INST * 2, 2	);
	SetOp( RESULT_SSE_ADDPD_IRS4,		PER_LOOP_INST * 2, 2	);




	SetOp( RESULT_AVX_VMULPD_IR8,		PER_LOOP_INST * 4, 4	);
	SetOp( RESULT_AVX_VADDPD_IR8,		PER_LOOP_INST * 4, 4	);
	SetOp( RESULT_AVX_VMULPD_VADDPD_IR8,PER_LOOP_INST * 4, 4	);
	SetOp( RESULT_AVX_VFMADDPD_IR8,		PER_LOOP_INST * 8, 8	);


	SetOp( RESULT_AVX_VML_AD_VADDPD_IR9,PER_LOOP_INST_9 * 4, 4	);


}






//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------



SSE_S_IR8( mulsd,  mulsd_ir8 );
SSE_S_IR8( addsd,  addsd_ir8 );
SSE_S_FMA_IR8( vfmadd213sd,  fmaddsd_ir8 );

SSE_S_IR8( mulpd,  mulpd_ir8 );
SSE_S_IR8( addpd,  addpd_ir8 );
SSE_M_IR8( mulpd, addpd,  mulpd_addpd_ir8 );
SSE_S_FMA_IR8( vfmadd213pd,  fmaddpd_ir8 );


SSE_M_IR9( mulpd, addpd, addpd, ml_ad_addpd_ir9 );



SSE_S_IRS4( mulsd,  mulsd_irs4 );
SSE_S_IRS4( addsd,  addsd_irs4 );

SSE_S_IRS4( mulpd,  mulpd_irs4 );
SSE_S_IRS4( addpd,  addpd_irs4 );



AVX_S_IR8( vmulpd,  vmulpd_ir8 );
AVX_S_IR8( vaddpd,  vaddpd_ir8 );
AVX_M_IR8( vmulpd, vaddpd,  vmulpd_vaddpd_ir8 );
AVX_S_FMA_IR8( vfmadd213pd,  vfmaddpd_ir8 );



AVX_M_IR9( vmulpd, vaddpd, vaddpd, vml_ad_vaddpd_ir9 );





void FloatTest::Run()
{
	ClearResult();
	unsigned int	Loop= LoopCount;

FL_LOG( "SSE loop=%d\n", Loop );

	double	sum= 0;
	double	sum_2= 0;
	for( unsigned int i= 0 ; i< Loop * 5 ; i++ ){
		sum+= 2.0f;
		sum_2+= 10.0f;
	}




	//------------------------------------------------------
	// IR8
	//------------------------------------------------------
	SetResult( RESULT_SSE_MULSD_IR8,	SSE_S_IR8_mulsd_ir8( Loop, 10.0f		) );
	Progress++;

	SetResult( RESULT_SSE_ADDSD_IR8,	SSE_S_IR8_addsd_ir8( Loop, 10.0f		) );
	Progress++;

	if( Info.HasInstructionSet( CPUFeature::IA_FMA3 ) ){

		SetResult( RESULT_SSE_FMADDSD_IR8,	SSE_S_FMA_IR8_fmaddsd_ir8( Loop, 10.0f		) );
		Progress++;

	}else{
		Progress++;
	}




	SetResult( RESULT_SSE_MULPD_IR8,	SSE_S_IR8_mulpd_ir8( Loop, 10.0f		) );
	Progress++;

	SetResult( RESULT_SSE_ADDPD_IR8,	SSE_S_IR8_addpd_ir8( Loop, 10.0f		) );
	Progress++;


	SetResult( RESULT_SSE_MULPD_ADDPD_IR8,	SSE_M_IR8_mulpd_addpd_ir8( Loop, 10.0f		) );
	Progress++;


	if( Info.HasInstructionSet( CPUFeature::IA_FMA3 ) ){

		SetResult( RESULT_SSE_FMADDPD_IR8,	SSE_S_FMA_IR8_fmaddpd_ir8( Loop, 10.0f		) );
		Progress++;

	}else{
		Progress++;
	}



	//------------------------------------------------------
	// IR9
	//------------------------------------------------------

	SetResult( RESULT_SSE_ML_AD_ADDPD_IR9,	SSE_M_IR9_ml_ad_addpd_ir9( Loop, 10.0f		) );
	Progress++;



	//------------------------------------------------------
	// IRS4
	//------------------------------------------------------
	SetResult( RESULT_SSE_MULSD_IRS4,	SSE_S_IRS4_mulsd_irs4( Loop, 10.0f		) );
	Progress++;

	SetResult( RESULT_SSE_ADDSD_IRS4,	SSE_S_IRS4_addsd_irs4( Loop, 10.0f		) );
	Progress++;



	SetResult( RESULT_SSE_MULPD_IRS4,	SSE_S_IRS4_mulpd_irs4( Loop, 10.0f		) );
	Progress++;

	SetResult( RESULT_SSE_ADDPD_IRS4,	SSE_S_IRS4_addpd_irs4( Loop, 10.0f		) );
	Progress++;






	//------------------------------------------------------
	//------------------------------------------------------


	//------------------------------------------------------
	// AVX
	//------------------------------------------------------

	if( Info.HasInstructionSet( CPUFeature::IA_AVX ) ){

		//------------------------------------------------------
		// IR8
		//------------------------------------------------------
		SetResult( RESULT_AVX_VMULPD_IR8,	AVX_S_IR8_vmulpd_ir8( Loop, 10.0f		) );
		Progress++;

		SetResult( RESULT_AVX_VADDPD_IR8,	AVX_S_IR8_vaddpd_ir8( Loop, 7.0f		) );
		Progress++;


		SetResult( RESULT_AVX_VMULPD_VADDPD_IR8,	AVX_M_IR8_vmulpd_vaddpd_ir8( Loop, 7.0f		) );
		Progress++;


		if( Info.HasInstructionSet( CPUFeature::IA_FMA3 ) ){

			SetResult( RESULT_AVX_VFMADDPD_IR8,	AVX_S_FMA_IR8_vfmaddpd_ir8( Loop, 10.0f		) );	// **!!!** 15
			Progress++;

		}else{
			Progress++;
		}



		//------------------------------------------------------
		// IR9
		//------------------------------------------------------
		SetResult( RESULT_AVX_VML_AD_VADDPD_IR9,	AVX_M_IR9_vml_ad_vaddpd_ir9( Loop, 7.0f		) );
		Progress++;


	}

	//------------------------------------------------------
	//------------------------------------------------------

	DoneFlag= true;
}


const char*	FloatTest::GetInstructionName( unsigned int result_index ) const
{
	flASSERT( result_index < GetResultCount() );
	flASSERT( sizeof(Instruction_Title)/sizeof(const char*) == GetResultCount() );
	return	Instruction_Title[result_index];
}

const char*	FloatTest::GetTestName() const
{
	if( !IsMultithread() ){
		return	"SSE/AVX (DP fp)";
	}else{
		return	"SSE/AVX (DP fp) multi-thread";
	}
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
}

//-----------------------------------------------------------------------------
#endif // x86
//-----------------------------------------------------------------------------

