#include <textstream.h>
#include <stringstream.h>
#include <iostream>

class StdoutStream : public TextStream
{
public:
	StdoutStream() : TextStream()
	{

	}

	void put_byte(uint8_t c)
	{
		std::cout << c ;
	}

} ;

void test_StringStream() ;

int main()
{
	StdoutStream s ;

	s << "decimal: " << 5 << " " << -5 << "\n" ;
	s << "decimal: " << 5u << " " << -5u << "\n" ;

	s << "float3p2: " << float3p2(1.55) << "\n" ;
	s << "float3p2: " << float3p2(-999.99) << "  " << float3p2(999.99) << "\n" ;

	s << "prefix: " << prefix(5000000000, "A") << "\n" ;
	s << "prefix: " << prefix(500000000, "A") << "\n" ;
	s << "prefix: " << prefix(50000000, "A") << "\n" ;
	s << "prefix: " << prefix(5000000, "A") << "\n" ;
	s << "prefix: " << prefix(500000, "A") << "\n" ;
	s << "prefix: " << prefix(50000, "A") << "\n" ;
	s << "prefix: " << prefix(5000, "A") << "\n" ;
	s << "prefix: " << prefix(500, "A") << "\n" ;
	s << "prefix: " << prefix(50, "A") << "\n" ;
	s << "prefix: " << prefix(5, "A") << "\n" ;
	s << "prefix: " << prefix(0.5, "A") << "\n" ;
	s << "prefix: " << prefix(0.05, "A") << "\n" ;
	s << "prefix: " << prefix(0.005, "A") << "\n" ;
	s << "prefix: " << prefix(0.0005, "A") << "\n" ;
	s << "prefix: " << prefix(0.00005, "A") << "\n" ;
	s << "prefix: " << prefix(0.000005, "A") << "\n" ;
	s << "prefix: " << prefix(0.0000005, "A") << "\n" ;
	s << "prefix: " << prefix(0.00000005, "A") << "\n" ;
	s << "prefix: " << prefix(0.000000005, "A") << "\n" ;

	s << "bin 8 bits: " << bin8(5) << "\n" ;
	s << "bin 16 bits: " << bin16(5) << "\n" ;
	s << "bin 32 bits: " << bin32(5) << "\n" ;

	s << "hex 8 bits: " << hex8(0x12) << "\n" ;
	s << "hex 16 bits: " << hex16(0x1234) << "\n" ;
	s << "hex 32 bits: " << hex32(0x12345678) << "\n" ;

	test_StringStream() ;
}

void test_StringStream()
{
	char buff[100] ;
	StringStream s(buff, sizeof(buff)) ;

	s.put_byte('a') ;
	s.put_byte('b') ;
	s.put_byte('c') ;
	std::cout << s.c_str() << std::endl ;
	std::cout << (char)s.read_byte() << std::endl ;
	std::cout << s.c_str() << std::endl ;

	s.left() ;
	s.put_byte('d') ;
	std::cout << s.c_str() << std::endl ;

	s.clear() ;
	s << 200 ;
	std::cout << s.c_str() << std::endl ;

	uint32_t i=0 ;
	s >> i ;
	std::cout << i << std::endl ;

	s.clear() ;
	s << -299 ;
	std::cout << s.c_str() << std::endl ;

	int32_t i2=0 ;
	s >> i2 ;
	std::cout << i2 << std::endl ;
}
