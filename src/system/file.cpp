#include "../../include/system/file.h"

File::File(){}
File::~File(){
	if(fileStream.is_open()){ fileStream.close(); }
}

void File::open(const std::string& fileName, std::string mode){
	if (fileStream.is_open()) {
		fileStream.close();
	}
	std::ios_base::openmode openMode;
	switch(mode.size()){
		case 1:{
			if(mode == "r"){
				openMode = std::ios::in;
			}else if(mode == "w"){
				openMode = std::ios::out | std::ios::trunc;
			}else if(mode == "a"){
				openMode = std::ios::out | std::ios::app;
			}
		}break;
		case 2:{
			if(mode == "rb"){
				openMode = std::ios::in | std::ios::binary;
			}else if(mode == "wb"){
				openMode = std::ios::out | std::ios::trunc | std::ios::binary;
			}else if(mode == "ab"){
				openMode = std::ios::out | std::ios::app | std::ios::binary;
			}else if(mode == "rw"){
				openMode = std::ios::in | std::ios::out;
			}
		}break;
		case 3:{
			if(mode == "rwb"){
				openMode = std::ios::in | std::ios::out | std::ios::binary;
			}
		}break;
	}
	fileStream.open(fileName, openMode);
	if (!fileStream.is_open()) {
		err=1;
		return;
	}
	err = 0;
}
void File::close(){ if(fileStream.is_open()){ fileStream.close(); } };

std::string File::readLine() {
	if (!fileStream.is_open()) {
		err = 1;
		return "";
	}
	
	if (fileStream.flags() & std::ios::binary) {
		err = 1;
		return "";
	}
	std::string line;
	std::getline(fileStream, line);
	if(!fileStream.fail()){
		err = 1;
		return "";
	}
	err = 0;
	return line;
}
char File::getChar() {
	if (!fileStream.is_open()) {
		err = 1;
		return 0;
	}
	char ch;
	if (fileStream.flags() & std::ios::binary) {
		fileStream.read(&ch, sizeof(char));
		if (!fileStream.good()) {
			err = 1;
			return 0;
		}
	} else {
		fileStream.get(ch);
		if (!fileStream.good()) {
			err = 1;
			return 0;
		}
	}
	err = 0;
	return ch;
}
std::string File::readAll(){
	if (!fileStream.is_open()) {
		err = 1;
		return "";
	}
	std::stringstream str;
	str << fileStream.rdbuf();
	if(fileStream.fail()){
		err = 1;
		return "";
	}
	return str.str();
}
void File::setChar(char ch) {
	if (!fileStream.is_open()) {
		err = 1;
		return;
	}
	
	if (fileStream.flags() & std::ios::binary) {
		fileStream.write(&ch, sizeof(char));
		if (!fileStream.good()) {
			err = 1;
			return;
		}
	} else {
		fileStream.put(ch);
		if (!fileStream.good()) {
			err = 1;
			return;
		}
	}
	err = 0;
}

bool File::end(){
	if(fileStream.eof()){
		fileStream.clear();
		return 1;
	}
	return 0;
}

void File::setPos(int64_t pos){
	if (fileStream.is_open()) {
		fileStream.seekg(pos, std::ios::beg);
		if (!fileStream.fail()) {
			err = 0;
			return;
		}
	}
	err = 1;
}

int64_t File::getPos(){
	if (fileStream.is_open()) {
		err = 0;
		return static_cast<int64_t>(fileStream.tellg());
	}
	err = 1;
	return 0;
}



bool File::Err(){
	if(err){
		err = 0;
		return 1;
	}
	return 0;
}






