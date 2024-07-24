//
// Created by liwenjie on 2024/5/31.
//

#ifndef NDB_NDB_H
#define NDB_NDB_H

namespace ndb {
    class NDB {
    public:
        void GetNDB(); // 单例模式

        // 读取文件，构建网表数据库
        void ReadLibrary();
        void ReadVerilog();

        // 动态构建网表数据库
        void CreateNetlist();
        void DeleteNetlist();

        void CreateLibrary();
        void DeleteLibrary();

        void CreateModule();
        void DeleteModule();

        void CreateInstance();
        void DeleteInstance();

        void CreatePort();
        void DeletePort();

        void CreatePin();
        void DeletePin();

        void CreateNet();
        void DeleteNet();

        void CreateAssign();
        void DeleteAssign();

        void CreateConnection();
        void DeteleConnection();

        void CreateFlattenModel();
        void DeleteFlattenModel();

        // 添加DFT测试相关API
    private:
        // 单例模式
    private:
        // 调用 verilog parser
        // 调用 library parser
        // 保存library
        // 保存netlist
        // 保存flatten model
    };
}
#endif//NDB_NDB_H
