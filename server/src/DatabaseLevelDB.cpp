#include "DatabaseLevelDB.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "DatabaseWriteBatch.h"

using namespace leveldb;

DatabaseLevelDB::DatabaseLevelDB() : db(NULL), db_path("")
{

}

DatabaseLevelDB::~DatabaseLevelDB()
{
    this->close();
}

Status DatabaseLevelDB::config(const std::string& db_path, bool create_if_missing, bool clean){
    if(this->db != NULL){
        return Status::NotFound(""); // agregar msg de error?
    }
    this->db_path = db_path; // chequear si es valido?
    this->create_if_missing = create_if_missing;
    this->clean_on_start = clean;
    return Status::OK();
}

Status DatabaseLevelDB::open(){
    if(db_path.compare("") == 0){
        return Status::NotFound("");
    }
    if(db != NULL){
        return Status::NotFound("");
    }

    Options options;
    options.create_if_missing = create_if_missing;

    Status s = DB::Open(options, db_path, &db);
    if(s.ok() && this->clean_on_start){
        this->clean_on_start = false;
        s = this->clear_all();
    }
    return s;
}

void DatabaseLevelDB::close(){
    if(db != NULL){
        delete db;
        db = NULL;
    }
}

Status DatabaseLevelDB::put(DBElement &elem){
    if(db == NULL)
        return Status::NotFound("No se inicializo la base de datos");
    Status s = db->Put(WriteOptions(), elem.getKey(), elem.getValue());
    if(!s.ok())
        return Status::NotFound("Error interno en la base de datos al guardar el registro");
    return s;
}

Status DatabaseLevelDB::get(DBElement &elem){
    if(db == NULL)
        return Status::NotFound("la base de datos no fue creada");
    std::string get_result;
    //std::cout << "elem key antes: " << elem.getKeyToString() << std::endl;
    //std::cout << "elem val antes: " << elem.getValueToString() << std::endl;
    Status s = db->Get(ReadOptions(), elem.getKey(), &get_result);
    if(!s.ok()){
        return Status::NotFound("No se encontro el registro");
    }
    //std::cout << "get_res: " << get_result << std::endl;
    elem.setValue(get_result);
    //std::cout << "elem key despues: " << elem.getKeyToString() << std::endl;
    //std::cout << "elem val despues: " << elem.getValueToString() << std::endl;

    return s;
}

Status DatabaseLevelDB::erase(DBElement &elem){
    if(db == NULL)
        return Status::NotFound("");
    return db->Delete(WriteOptions(), elem.getKey());
}

Status DatabaseLevelDB::writeBatch(DatabaseWriteBatch *batch){
    if(db == NULL)
        return Status::NotFound("");

    WriteOptions wo;
    wo.sync = true; // esto no se si va

    std::vector<std::string> *keys = batch->getKeys();
    std::vector<std::string> *values = batch->getValues();
    std::vector<std::string> *operations = batch->getOperations();
    WriteBatch rdb_batch;
    std::string key = "";
    std::string value = "";
    for(int i = 0, size = operations->size(); i < size; ++i){
        if(operations->at(i) == "erase"){
            rdb_batch.Delete(keys->at(i));
        } else if(operations->at(i) == "put"){
            rdb_batch.Put(keys->at(i), values->at(i));
        } else {
            //error
        }
    }

    return db->Write(wo, &rdb_batch);
}

Status DatabaseLevelDB::clear_all(){
    if(db == NULL)
        return Status::NotFound("");
    Status s;
    leveldb::Iterator* it = db->NewIterator(ReadOptions());
    for(it->SeekToFirst(); it->Valid(); it->Next()){
        s = db->Delete(WriteOptions(), it->key());
        if(!s.ok()){
            return s;
        }
    }
    if(!it->status().ok()){
        return it->status();
    }
    delete it;
    return s;
}
