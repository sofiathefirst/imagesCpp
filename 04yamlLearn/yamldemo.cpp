#include "yaml-cpp/yaml.h"
#include <iostream>
#include<fstream>
//https://blog.csdn.net/CAIYUNFREEDOM/article/details/89680915
//https://github.com/jbeder/yaml-cpp

using namespace std;
int main() {
	YAML::Node config = YAML::LoadFile(
			"test.yaml");
	const std::string username = config["username"].as<std::string>();
	const std::string password = config["password"].as<std::string>();
	int age = config["age"].as<int>();
	float money = config["money"].as<float>();
	cout << username << endl << password << endl << age<<endl<<money<<endl;

	YAML::Emitter out;
	//out << YAML::BeginSeq;
	//out << YAML::Anchor("fred");
	out << YAML::BeginMap;
	out << YAML::Key << "name" << YAML::Value << "Fred";
	out << YAML::Key << "age" << YAML::Value << "42";
	out << YAML::EndMap;
	//out << YAML::Alias("fred");
	//out << YAML::EndSeq;

	 std::ofstream fout("writer.yaml");
	        fout << out.c_str();
	        fout.close();

	return 0;
}
