
#include "gtest/gtest.h"
#include "JsonSerializer.h"
#include "json/json.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define ERROR "error"

using namespace Json;

TEST(JsonSerializerTest, CrearValueNombreValor){
    std::string name = "matias";
    std::string val = "valor";

    std::string val_json = "";

    JsonSerializer serializer;
    serializer.addValueToObjectList(val_json, name, val);
    serializer.turnObjectListToObject(val_json);

    Reader reader;
    Value value;
    reader.parse(val_json, value);

    std::string str_res = "";
    Value val_res;
    serializer.get(value, name, ERROR, val_res, str_res);
    EXPECT_TRUE(str_res.compare(val) == 0);
}

TEST(JsonSerializerTest, CrearListaValuesNombreValor){

    std::string val_json = "";

    JsonSerializer serializer;
    serializer.addValueToObjectList(val_json, "gonzalo", "guzzardi");
    serializer.addValueToObjectList(val_json, "matias", "carballo");
    serializer.addValueToObjectList(val_json, "juampa", "marshall");
    serializer.addValueToObjectList(val_json, "federico", "baliña");
    serializer.turnObjectListToObject(val_json);

    Reader reader;
    Value value;
    reader.parse(val_json, value);

    Value res;
    std::string str_res;

    serializer.get(value, "gonzalo", ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare("guzzardi") == 0);
    serializer.get(value, "matias", ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare("carballo") == 0);
    serializer.get(value, "juampa", ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare("marshall") == 0);
    serializer.get(value, "federico", ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare("baliña") == 0);
}

TEST(JsonSerializerTest, CrearArrayValuesNombreValor){

    std::string val_json = "";

    JsonSerializer serializer;
    serializer.addValueToArrayList(val_json, "gonzalo");
    serializer.addValueToArrayList(val_json, "matias");
    serializer.addValueToArrayList(val_json, "juampa");
    serializer.addValueToArrayList(val_json, "federico");
    serializer.turnArrayListToArray(val_json, "nombres");
    serializer.turnObjectListToObject(val_json);

    Reader reader;
    Value value;
    reader.parse(val_json, value);

    Value res_array, res;
    std::string str_res;

    serializer.get(value, "nombres", ERROR, res_array, str_res);
    serializer.get(res_array, 0, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);

    serializer.get(res_array, 1, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);

    serializer.get(res_array, 2, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);

    serializer.get(res_array, 3, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);
}

TEST(JsonSerializerTest, CrearArrayValuesDeVectorNombreValor){

    std::string val_json = "";
    JsonSerializer serializer;

    std::vector<std::string> nombres;
    nombres.push_back("gonzalo");
    nombres.push_back("matias");
    nombres.push_back("juampa");
    nombres.push_back("federico");

    serializer.turnVectorToArray(nombres, "nombres", val_json);
    serializer.turnObjectListToObject(val_json);

    Reader reader;
    Value value;
    reader.parse(val_json, value);

    Value res_array, res;
    std::string str_res;

    serializer.get(value, "nombres", ERROR, res_array, str_res);
    serializer.get(res_array, 0, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);

    serializer.get(res_array, 1, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);

    serializer.get(res_array, 2, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);

    serializer.get(res_array, 3, ERROR, res, str_res);
    EXPECT_TRUE(str_res.compare(ERROR) != 0);
}

TEST(JsonSerializerTest, userMetadataSerialization){

	std::string join_date = "26/09/2015";

	JsonSerializer serializer;

	std::string val_date_joined = "";
	serializer.addValueToObjectList(val_date_joined, "join_date", join_date);

	std::string val_json = "";
	serializer.joinValueIntoList(val_json, val_date_joined);
	serializer.turnObjectListToObject(val_json);

	std::ofstream log;
	log.open("JsonSerializer_unittest_LOG.txt", std::ios::app);
	if (!log){
		log.open("JsonSerializer_unittest_LOG.txt", std::ios::trunc);
	}
	log << "Json armado: " << std::endl;
	log << val_json << std::endl;

	Reader reader;
	Value value;
	reader.parse(val_json, value);
	log << "Json parseado: " << std::endl;
	log << value.toStyledString() << std::endl;
	log.close();

}
