#ifndef Termb_H
#define Termb_H

#include <uv.h>
#include <node.h>
#include <node_buffer.h>
#include <node_object_wrap.h>

class Termb : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> exports);

private:
	explicit Termb();
	~Termb();

	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void InitComm(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void CloseComm(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Authenticate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Read_Content(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetPeopleName(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetPeopleSex(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetPeopleNation(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetPeopleBirthday(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetPeopleAddress(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetPeopleIDCode(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetStartDate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void GetEndDate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Persistent<v8::Function> constructor;
};

#endif