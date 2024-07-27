#include <iostream>

#include <array>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <type_traits>


template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
printIP(const T& val, std::ostream& stream){
	constexpr size_t len(sizeof(T));
	static_assert(len>0," sizeof returned negative value?! ");
	
	std::array<unsigned char, len> bytes;	
	std::memcpy(bytes.data(), &val, len);
	
	for(auto i=len-1;i>0;--i)
		stream << std::to_string(bytes.at(i)) << ".";
	stream << std::to_string(bytes.at(0));
	stream << std::endl;
}


void printIP (const std::string& val, std::ostream& stream){
	stream << val << std::endl;
}

template<class T>
typename std::enable_if<std::is_same<T, std::vector <typename T::value_type> >::value
						|| std::is_same<T, std::list <typename T::value_type> >::value
					,void>::type 
printIP(const T& container, std::ostream& stream){
	
	auto first = container.begin();
	auto last = container.end();
	
	if(first!=last){
		for(--last; first!=last; ++first)
			stream << std::to_string(*first) <<".";
		stream << std::to_string(*first) <<std::endl;
	}
}


int main(int argc, char const *argv[])
{
    try
    {	
		printIP(char(-1), std::cout);
		printIP(short(0), std::cout);
		printIP(int(2130706433), std::cout);
		printIP((long long)(8875824491850138409), std::cout);

		printIP(std::string("1.2.3.4.5.6.7.8.99"), std::cout);
				
		printIP(std::vector<int>{0x012345,0x987654,0x112233}, std::cout);
		printIP(std::vector<unsigned char>{0x11,0x22,0x33,0x44}, std::cout);
		printIP(std::list<int>{0x012345,0x987654,0x112233}, std::cout);
		printIP(std::list<long long>{75824491850138409,75824491850138408,75824491850138410,75824491850138407}, std::cout);
				
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}