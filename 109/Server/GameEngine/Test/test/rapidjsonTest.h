#include "framework/json/value.h"
#include "framework/rapidjson/document.h"
#include "framework/rapidjson/stringbuffer.h"
#include "framework/rapidjson/writer.h"
#include "../TestDef.h"

using namespace rapidjson;

std::string getRapidjsonStr(const Document& d) {
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);
	return buffer.GetString();
}

std::string getRapidjsonStr(rapidjson::Value& jv) {
	Document d;
	d.AddMember("print", jv, d.GetAllocator());
	return getRapidjsonStr(d);
}

void testRapidJson(Json::Value &js) {

	const char* json = "{\"project\":\"GameWorld\",\"version\":108}";
	Document d;
	d.Parse(json);

	rapidjson::Value& v = d["version"];
	v.SetInt(v.GetInt() + 2);

	LogDebug("rapidjson str1=" <<getRapidjsonStr(d));

	d.AddMember("test", true, d.GetAllocator());

	LogDebug("rapidjson str2=" << getRapidjsonStr(d));

	rapidjson::Value jv;
	rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
	jv.SetArray();
	jv.PushBack(101, allocator);
	jv.PushBack(102, allocator);
	jv.PushBack(103, allocator);
	d.AddMember("array", jv, d.GetAllocator());

	LogDebug("rapidjson str3=" << getRapidjsonStr(d));

	d.RemoveMember("test");

	rapidjson::Value& arrayJv = d["array"];
	int i2 = arrayJv[1].GetInt();

	LogDebug("rapidjson str4=" << getRapidjsonStr(d));

	LogDebug("rapidjson i" <<i2);

	arrayJv[1] = 188;

	LogDebug("rapidjson str5=" << getRapidjsonStr(d));

	onlyQForExit();
}



void testRapidJson() {
	Json::Value js;
	testRapidJson(js);
}