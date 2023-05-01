
#ifndef _BUFFERED_INPUT_STREAM_
#define _BUFFERED_INPUT_STREAM_

#include <cstdio>

namespace pvm {

#define BUFFER_LEN 256

class BufferedInputStream {

public:
    BufferedInputStream(const char * file_name) {
        m_fp = fopen(file_name, "rb");
        fread(m_sz_buffer, BUFFER_LEN * sizeof(char), 1, m_fp);
        m_index = 0;
    }

    ~BufferedInputStream() {
        Close();
    }

    char Read() {
        if (m_index < BUFFER_LEN) {
            return m_sz_buffer[m_index++];
        } else {
            m_index = 0;
            fread(m_sz_buffer, BUFFER_LEN * sizeof(char), 1, m_fp);
            return m_sz_buffer[m_index++];
        }

    }

    int ReadInt() {
        int b1 = Read() & 0xFF;
        int b2 = Read() & 0xFF;
        int b3 = Read() & 0xFF;
        int b4 = Read() & 0xFF;

        return b4 << 24 | b3 << 16 | b2 << 8 | b1;
    }

    void UnRead() {
        m_index--;
    }

    void Close() {
        if (m_fp != nullptr) {
            fclose(m_fp);
            m_fp = nullptr;
        }
    }

private:
    /* data */

    FILE* m_fp {nullptr};
    char m_sz_buffer[BUFFER_LEN];
    unsigned short m_index;
};

}



#endif 