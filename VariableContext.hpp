#pragma once
class VariableContext {
	//atrapa
	//to miał napisać Jałokim,
	//obsługa katalogów i zmiennych
	int ret;
	public:
	std::string getPath() {
		return std::string(getenv("PATH"));
		//to może być inaczej
	}
	
	void setReturn(int ret) {
		this->ret = ret;
	}

};
