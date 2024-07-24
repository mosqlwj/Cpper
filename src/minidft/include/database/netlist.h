//
// Created by liwenjie on 2023/4/27.
//

#ifndef NDB_NETLIST_H
#define NDB_NETLIST_H

#include "module.h"
#include "library.h"
#include "flat_model.h"
#include "lib_cell.h"

#include <iostream>

namespace ndb {

class Netlist {
public:
    void Report();

    void SetTopModule(Module* top_module) { top_module_ = top_module;}
    Module* GetTopModule() const { return top_module_;}

    void SetLibrary(Library* lib) {
        assert(lib);
        library_ = lib;
    }

    Library* GetLibrary() const { return library_;}

    FlatModel* CreateFlatModel(Module* top_module);
    FlatModel* GetFlatModel() const { return flat_model_;}

    void Link();

    void Uniquify(Module* module);
    void Flatten(Module* module);  // gate level netlist
private:
    // 保存top module
    Module* top_module_;
    // 保存library
    Library* library_;
    // 保存flat model
    FlatModel* flat_model_;

    // 保存所有hier name->instance map

    // 保存所有hier name->pin map

    // 保存所有hier name->net map



};

}

#endif // NDB_NETLIST_H
