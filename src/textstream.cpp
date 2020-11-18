#include <textstream.h>
#include <cctype>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"

TextStream::TextStream()
	: Stream()
{

}

TextStream& operator<<(TextStream& stream, char c)
{
	stream.put_byte(c) ;
	return stream ;
}

TextStream& operator<<(TextStream& stream, uint8_t c)
{
	stream.put_byte(c) ;
	return stream ;
}

TextStream& operator<<(TextStream& stream, const char* s)
{
	while(*s!='\0')
	{
		stream << *s ;
		s++ ;
	}
	return stream ;
}

TextStream& operator<<(TextStream& stream, int32_t v)
{
	char buff[12] ;
	char* c=buff+11 ;

	*c = '\0' ;
	c-- ;

	if(v<0)
	{
		stream << '-' ;
		v = -v ;
	}
	if(v==0)
		stream << '0' ;
	else
	{
		while(v>0)
		{
			*c = '0'+v%10 ;
			v /= 10 ;
			if(v>0)
				c-- ;
		}
		stream << c ;
	}
	return stream ;
}

TextStream& operator<<(TextStream& stream, uint32_t v)
{
	char buff[12] ;
	char* c=buff+11 ;

	*c = '\0' ;
	c-- ;

	if(v==0)
		stream << '0' ;
	else
	{
		while(v>0)
		{
			*c = '0'+v%10 ;
			v /= 10 ;
			if(v>0)
				c-- ;
		}
		stream << c ;
	}
	return stream ;
}

#ifdef STREAM_SUPPORT_FLOAT

float3p2_float_t float3p2(float v)
{
	return {v} ;
}

TextStream& operator<<(TextStream& stream, float3p2_float_t v)
{
	const int precision=100 ;
	int sign=1 ;

	if(v.v<0)
	{
		sign = -1 ;
		v.v = -v.v ;
	}
	v.v += 0.005 ;

	int ent=(int)v.v ;
	int frac=((int)(v.v*precision)%precision) ;

	if(sign==-1 && (ent!=0 || frac!=0))
		stream << '-' ;

	if(ent==0)
		stream << '0' ;
	else
	{
		bool put=false ;
		int p=100 ;
		for(int i=0 ; i<3 ; i++)
		{
			char n=ent/p ;
			ent = ent%p ;
			p /= 10 ;
			if(put==true || n>0)
			{
				stream << (char)('0'+n) ;
				put = true ;
			}
		}
	}

	stream << '.' ;
	if(frac>0)
	{
		int p=10 ;
		for(int i=0 ; i<2 ; i++)
		{
			if(frac==0)
				break ;

			char n=frac/p ;
			frac = frac%p ;
			p /= 10 ;
			stream << (char)('0'+n) ;
		}
	}

	return stream ;
}


const char dsuffix[]={'\0', 'k', 'M', 'G'} ;
const char fsuffix[]={'\0', 'm', 'u', 'n', 'p', 'f'} ;

prefix_float_t prefix(float v, const char* p)
{
	return {v, p} ;
}

TextStream& operator<<(TextStream& stream, prefix_float_t v)
{
	int sign=1 ;
	if(v.v<0)
	{
		sign = -1 ;
		v.v = -v.v ;
	}

	if(v.v>=1)
	{
		bool p=false ;
		for(int si=0 ; si<(int)sizeof(dsuffix) ; si++)
		{
			if(v.v<1000)
			{
				stream << float3p2(v.v*sign) ;
				if(si>0)
					stream << dsuffix[si] ;
				p = true ;
				break ;
			}
			else
				v.v /= 1000 ;
		}
		if(p==false)
			stream << "#OVF" ;
		else
			stream << v.unit ;
	}
	else
	{
		bool p=false ;
		for(int si=0 ; si<(int)sizeof(fsuffix) ; si++)
		{
			if(v.v>0.9)
			{
				stream << float3p2(v.v*sign) ;
				if(si>0)
					stream << fsuffix[si] ;
				p = true ;
				break ;
			}
			else
				v.v *= 1000 ;
		}
		if(p==false)
			stream << float3p2(0.) ;
		stream << v.unit ;
	}
	return stream ;
}
#endif

bin8_uint32_t bin8(uint32_t v)
{
	return {v} ;
}

TextStream& operator<<(TextStream& stream, bin8_uint32_t v)
{
	char buff[9] ;
	char* b=buff+8 ;

	buff[8] = '\0' ;
	*b = 0 ;
	b-- ;
	for(int i=0 ; i<8 ; i++)
	{
		*b = '0'+(v.v & 1) ;
		v.v >>= 1 ;
		b-- ;
	}
	stream << buff ;
	return stream ;
}

bin16_uint32_t bin16(uint32_t v)
{
	return {v} ;
}

TextStream& operator<<(TextStream& stream, bin16_uint32_t v)
{
	char buff[17] ;
	char* b=buff+16 ;

	buff[16] = '\0' ;
	*b = 0 ;
	b-- ;
	for(int i=0 ; i<16 ; i++)
	{
		*b = '0'+(v.v & 1) ;
		v.v >>= 1 ;
		b-- ;
	}
	stream << buff ;
	return stream ;
}

bin32_uint32_t bin32(uint32_t v)
{
	return {v} ;
}

TextStream& operator<<(TextStream& stream, bin32_uint32_t v)
{
	char buff[33] ;
	char* b=buff+32 ;

	buff[32] = '\0' ;
	*b = 0 ;
	b-- ;
	for(int i=0 ; i<32 ; i++)
	{
		*b = '0'+(v.v & 1) ;
		v.v >>= 1 ;
		b-- ;
	}
	stream << buff ;
	return stream ;
}


hex8_uint32_t hex8(uint32_t v)
{
	return {v} ;
}

TextStream& operator<<(TextStream& stream, hex8_uint32_t v)
{
	char buff[3] ;
	char* b=buff+2 ;

	buff[2] = '\0' ;
	*b = 0 ;
	b-- ;
	for(int i=0 ; i<2 ; i++)
	{
		if((v.v & 0x0F)<10)
			*b = '0'+(v.v & 0x0F) ;
		else
			*b = 'A'+((v.v & 0x0F)-10) ;
		v.v >>= 4 ;
		b-- ;
	}
	stream << buff ;
	return stream ;
}

hex16_uint32_t hex16(uint32_t v)
{
	return {v} ;
}

TextStream& operator<<(TextStream& stream, hex16_uint32_t v)
{
	char buff[5] ;
	char* b=buff+4 ;

	buff[4] = '\0' ;
	*b = 0 ;
	b-- ;
	for(int i=0 ; i<4 ; i++)
	{
		if((v.v & 0x0F)<10)
			*b = '0'+(v.v & 0x0F) ;
		else
			*b = 'A'+((v.v & 0x0F)-10) ;
		v.v >>= 4 ;
		b-- ;
	}
	stream << buff ;
	return stream ;
}

hex32_uint32_t hex32(uint32_t v)
{
	return {v} ;
}

TextStream& operator<<(TextStream& stream, hex32_uint32_t v)
{
	char buff[9] ;
	char* b=buff+8 ;

	buff[8] = '\0' ;
	*b = 0 ;
	b-- ;
	for(int i=0 ; i<8 ; i++)
	{
		if((v.v & 0x0F)<10)
			*b = '0'+(v.v & 0x0F) ;
		else
			*b = 'A'+((v.v & 0x0F)-10) ;
		v.v >>= 4 ;
		b-- ;
	}
	stream << buff ;
	return stream ;
}

TextStream& operator>>(TextStream& stream, uint32_t& v)
{
	uint8_t c=stream.read_byte() ;

	v = 0 ;
	while(isdigit(c))
	{
		v *= 10 ;
		v += c-'0' ;
		c = stream.read_byte() ;
	}

	return stream ;
}

TextStream& operator>>(TextStream& stream, int32_t& v)
{
	uint32_t sign=1 ;
	uint8_t c=stream.read_byte() ;

	if(c=='-')
	{
		sign = -1 ;
		c = stream.read_byte() ;
	}
	if(c=='+')
	{
		sign = 1 ;
		c = stream.read_byte() ;
	}

	v = 0 ;
	while(isdigit(c))
	{
		v *= 10 ;
		v += c-'0' ;
		c = stream.read_byte() ;
	}
	v *= sign ;

	return stream ;
}

#pragma GCC diagnostic pop
