#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cstdint>

class File{
	public:
		File();
		~File();
		
		void open(const std::string& fileName, std::string mode);
		void close();
		template <typename T>
		inline void write(T& data){
			if (!fileStream.is_open() || !(fileStream.flags() & std::ios::out)) {
				err = 1;
				return;
			}
			
			if (fileStream.flags() & std::ios::binary) {
				fileStream.write(reinterpret_cast<const char*>(&data), sizeof(T));
			} else {
				fileStream << data;
			}
			err = 0;
		}
		template <typename T>
		T read(){
			if (!fileStream.is_open()) {
				err = 1;
				T data;
				return data;
			}
			
			T data;
			if (fileStream.flags() & std::ios::binary) {
				fileStream.read(reinterpret_cast<char*>(&data), sizeof(T));
			} else {
				fileStream >> data;
			}
			if (fileStream.fail()) {
				err = 1;
				return data;
			}
			err = 0;
			return data;
		}
		std::string readLine();
		char getChar();
		std::string readAll();
		void setChar(char ch);
		bool end();
		void setPos(int64_t pos);
		int64_t getPos();
		
		bool Err();
	private:
		bool err=0;
		std::fstream fileStream;
};
