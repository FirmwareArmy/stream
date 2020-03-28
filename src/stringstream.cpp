#include <stringstream.h>
#include <cstring>

 StringStream::StringStream(char* buff, size_t size)
	: TextStream(),
	  _buff(buff),
	  _rpos(0),
 	  _wpos(0),
	  _size(size)
{
}

void StringStream::put_byte(uint8_t c)
{
	left() ;

	if(_wpos<_size-1)
	{
		_buff[_wpos] = c ;
		_buff[_wpos+1] = 0 ;
		_wpos++ ;
	}
}

uint8_t StringStream::read_byte()
{
	if(_rpos<_wpos)
	{
		_rpos++ ;
		return _buff[_rpos-1] ;
	}
	return 0 ;
}

size_t StringStream::size() const
{
	return strlen(_buff+_rpos) ;
}

void StringStream::left()
{
	if(_rpos==0)
		return ;

	size_t i=0 ;
	while(i+_rpos<_size && _buff[i+_rpos]!=0)
	{
		_buff[i] = _buff[i+_rpos] ;
		i++ ;
	}
	_buff[i] = 0 ;
	_wpos -= _rpos ;
	_rpos = 0 ;
}

const char* StringStream::c_str() const
{
	return _buff+_rpos ;
}

void StringStream::clear()
{
	_buff[0] = 0 ;
	_rpos = 0 ;
	_wpos = 0 ;
}
