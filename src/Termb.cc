#include "Termb.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace v8;

static WCHAR* UTF8toWCHAR(const char* inputString /** UTF-8 string. */)
{
	int outputSize;
	WCHAR* outputString;

	outputSize = MultiByteToWideChar(CP_UTF8, 0, inputString, -1, NULL, 0);

	if (outputSize == 0)
		return NULL;

	outputString = (WCHAR*)malloc(outputSize * sizeof(WCHAR));

	if (outputString == NULL) {
		SetLastError(ERROR_OUTOFMEMORY);
		return NULL;
	}

	if (MultiByteToWideChar(CP_UTF8, 0, inputString, -1, outputString, outputSize) != outputSize)
	{
		free(outputString);
		return NULL;
	}

	return outputString;
}

static std::string UTF8ToGBK(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	wchar_t * wszGBK = new WCHAR[len + 1]; memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (char*)strUTF8.c_str(), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL); //strUTF8 = szGBK; 
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}

static std::string GBKToUTF8(const std::string& strGBK)
{
	static std::string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n); n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

void* dlopen()
{
	WCHAR* unicodeFilename;
	void* handle;

	unicodeFilename = UTF8toWCHAR("termb.dll");

	if (unicodeFilename == NULL) {
		return NULL;
	}

	handle = (void*)LoadLibraryW(unicodeFilename);

	free(unicodeFilename);

	return handle;
}

Persistent<Function> Termb::constructor;

Termb::Termb(){
}

Termb::~Termb() {
}

void Termb::Init(Handle<Object> exports) {
	Isolate* isolate = Isolate::GetCurrent();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "Termb"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "InitComm", InitComm);
	NODE_SET_PROTOTYPE_METHOD(tpl, "CloseComm", CloseComm);
	NODE_SET_PROTOTYPE_METHOD(tpl, "Authenticate", Authenticate);
	NODE_SET_PROTOTYPE_METHOD(tpl, "Read_Content", Read_Content);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetPeopleName", GetPeopleName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetPeopleSex", GetPeopleName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetPeopleNation", GetPeopleName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetPeopleBirthday", GetPeopleName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetPeopleAddress", GetPeopleName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetPeopleIDCode", GetPeopleName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetStartDate", GetPeopleName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetEndDate", GetPeopleName);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "Termb"),
		tpl->GetFunction());
}

void Termb::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall()) {
		// Invoked as constructor: `new MyObject(...)`

		Termb* obj = new Termb();
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}
	else {
		// Invoked as plain function `MyObject(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] = { args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void Termb::InitComm(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int iPort = args[0]->Int32Value();

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(int nCom);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "InitComm"));

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(iPort);
			args.GetReturnValue().Set(Number::New(isolate, result));
		}
		else
		{
			args.GetReturnValue().Set(Number::New(isolate, 0));
		}
	}
}

void Termb::CloseComm(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)();
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "CloseComm"));

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)();
			args.GetReturnValue().Set(Number::New(isolate, result));
		}
		else
		{
			args.GetReturnValue().Set(Number::New(isolate, 0));
		}
	}
}

void Termb::Authenticate(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)();
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "Authenticate"));

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)();
			args.GetReturnValue().Set(Number::New(isolate, result));
		}
		else
		{
			args.GetReturnValue().Set(Number::New(isolate, 0));
		}
	}
}

void Termb::Read_Content(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int iActive = args[0]->Int32Value();

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(int iActive);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "Read_Content"));

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(iActive);
			args.GetReturnValue().Set(Number::New(isolate, result));
		}
		else
		{
			args.GetReturnValue().Set(Number::New(isolate, 0));
		}
	}
}

void Termb::GetPeopleName(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetPeopleName"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void Termb::GetPeopleSex(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetPeopleSex"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void Termb::GetPeopleNation(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetPeopleNation"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void Termb::GetPeopleBirthday(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetPeopleBirthday"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void Termb::GetPeopleAddress(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetPeopleAddress"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void Termb::GetPeopleIDCode(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetPeopleIDCode"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void Termb::GetStartDate(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetStartDate"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void Termb::GetEndDate(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	HMODULE module = (HMODULE)dlopen();
	if (module){
		using pInit = int(__stdcall *)(char* buf, int iLen);
		pInit procAddress = reinterpret_cast<pInit>(::GetProcAddress(module, "GetEndDate"));

		char* buf = new char[100];

		if (procAddress)
		{
			int result = reinterpret_cast<pInit>(procAddress)(buf, 100);

			if (result == 1)
			{
				std::string str = GBKToUTF8(buf);
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)str.c_str()));
			}
			else{
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
			}
		}
		else
		{
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
		}
	}
}

void InitAll(Handle<Object> exports) {
	Termb::Init(exports);
}

NODE_MODULE(termb, InitAll)