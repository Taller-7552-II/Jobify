
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "DatabaseLevelDB.h"
#include "leveldb/status.h"
#include "DBElement.h"

using namespace leveldb;
using namespace testing;

TEST(DatabaseTest, NoPuedoAbrirSinConfigurarla){
    DatabaseLevelDB db;
    leveldb::Status s = db.open();
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, CrearDBConfiguradaSatisfactoriamente){
    DatabaseLevelDB db;
    leveldb::Status s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());
}

TEST(DatabaseTest, NoPuedoConfigurarDBSiFueAbierta){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    s = db.config("/tmp/anotherDir", true);
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, NoPuedoAbrirDBSiYaFueAbierta){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_FALSE(s.ok());
}

// Segun google deberia ir con la clase que mockea
class MockDBElement : public DBElement {
    public:
        MockDBElement(Database* db) : DBElement(db){}
        void _setKey() { key = "clave"; }
        void _setValue() { value = "value"; }
        void _setValueVars() {}
};

class MockOtroDBElement : public DBElement {
    public:
	MockOtroDBElement(Database* db) : DBElement(db){}
        void _setKey() { key = "clave"; }
        void _setValue() { value = "value2"; }
        void _setValueVars() {}
};

class MockUnoMasDBElement : public DBElement {
    public:
	MockUnoMasDBElement(Database* db) : DBElement(db){}
        void _setKey() { key = "asd"; }
        void _setValue() { value = "asdasd"; }
        void _setValueVars() {}
};

TEST(DatabaseTest, GuardarYRecuperarElemento){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    s = db.clear_all();
    EXPECT_TRUE(s.ok());

    MockDBElement e_in(&db);
    s = db.put(e_in);
    EXPECT_TRUE(s.ok());

    MockDBElement e_out(&db);
    s = db.get(e_out);
    EXPECT_TRUE(s.ok());

    EXPECT_TRUE(e_in.getKeyToString().compare(e_out.getKeyToString()) == 0);
    EXPECT_TRUE(e_in.getValueToString().compare(e_out.getValueToString()) == 0);
}

TEST(DatabaseTest, GuardarDosClavesIgualesPisaElValor){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    s = db.clear_all();
    EXPECT_TRUE(s.ok());

    MockDBElement e_in1(&db);
    s = db.put(e_in1);
    EXPECT_TRUE(s.ok());

    MockOtroDBElement e_in2(&db);
    s = db.put(e_in2);
    EXPECT_TRUE(s.ok());

    MockOtroDBElement e_out2(&db);
    s = db.get(e_out2);
    EXPECT_TRUE(s.ok());

    EXPECT_FALSE(e_in1.getValueToString().compare(e_out2.getValueToString()) == 0);
    EXPECT_TRUE(e_in2.getValueToString().compare(e_out2.getValueToString()) == 0);
}

TEST(DatabaseTest, NoPuedoRecuperarDatoQueNoIngreseAntes){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    s = db.clear_all();
    EXPECT_TRUE(s.ok());

    MockUnoMasDBElement e_out(&db);
    s = db.get(e_out);
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, LimpiarDBBorraTodasLasClaves){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    MockDBElement e_in(&db);
    s = db.put(e_in);
    EXPECT_TRUE(s.ok());

    s = db.clear_all();
    EXPECT_TRUE(s.ok());

    MockDBElement e_out(&db);
    s = db.get(e_out);
    EXPECT_FALSE(s.ok());
    EXPECT_TRUE(s.IsNotFound());
}

TEST(DatabaseTest, NoPuedoLimpiarSiNoAbri){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.clear_all();
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, NoPuedoGuardarElemSinAbrirDB){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    MockDBElement e_in(&db);
    s = db.put(e_in);
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, NoPuedoRecuperarElemSinAbrirDB){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    MockDBElement e_out(&db);
    s = db.get(e_out);
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, NoPuedoBorrarElemSinAbrirDB){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    MockDBElement e_out(&db);
    s = db.erase(e_out);
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, BorrarNoDaErrorSiNoExisteLaClave){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    s = db.clear_all();
    EXPECT_TRUE(s.ok());

    MockDBElement e_out(&db);
    s = db.erase(e_out);
    EXPECT_TRUE(s.ok());
}

TEST(DatabaseTest, SiBorroClaveBorraElementoDeDB){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    MockDBElement e_in(&db);
    e_in.startBatch();
    s = db.put(e_in);
    EXPECT_TRUE(s.ok());

    s = db.erase(e_in);
    EXPECT_TRUE(s.ok());

    MockDBElement e_out(&db);
    s = db.get(e_out);
    EXPECT_FALSE(s.ok());
}

TEST(DatabaseTest, CreandoBatchLaSecuenciaDeOperacionesEsAtomica){
    DatebaseLevelDB db;
    leveldb::Status s;

    s = db.config("/tmp/test", true);
    EXPECT_TRUE(s.ok());

    s = db.open();
    EXPECT_TRUE(s.ok());

    MockDBElement e_in(&db);
    e_in.startBatch();
    s = e_in.put();
    EXPECT_TRUE(s.ok());

    MockDBElement e_out(&db);
    s = db.get(e_out);
    EXPECT_FALSE(s.ok());

    s = e_in.endBatch();
    EXPECT_TRUE(s.ok());

    s = db.get(e_out);
    EXPECT_TRUE(s.ok());
}