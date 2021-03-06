// 2013 Hiroyuki Ogasawara
// vim:ts=4 sw=4 noet:

#ifndef	PLATFORM_API_H_
#define	PLATFORM_API_H_

#include	<minilib/Platform.h>
#include	<stdint.h>

namespace flatlib {
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

namespace time {
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void	SleepMS( unsigned int ms );

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class TickTime {
#if FL_OS_WINDOWS
	int64_t	Freq;
#endif
public:
	TickTime();
	void	Init();
	int64_t	GetUS() const;
};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
}

namespace system {
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void	SetAffinityMask( uint64_t mask );
void	SetCpuAffinity( unsigned int cpu_index );

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
}

#endif

