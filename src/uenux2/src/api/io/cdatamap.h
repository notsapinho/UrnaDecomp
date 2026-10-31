// The reconstruction's note, not TSE's text. api::CDataMap<KeyType, RecordType>: a std::map, a cursor into it and a name
// the errors print. The layout is the bodies' (target fns 2919, 3892, 5377, 5725): the map at +0, the cursor at +12, the
// name at +16, 28 bytes, no vptr. The lines of the four throws, 98, 117, 143 and 158, are their records'; column 19 is
// `throw` at 12 spaces (class, body, if), which the class's own definitions fit; every other line is a choice, and so
// is where Find sits. The constructor from a name is the one comum::CCandidaturas's constructor (fn 5811) holds inlined,
// with the cursor at the map's end; const std::string& for its parameter is chosen (by value is not tried). IsFim is
// the cursor test fn 2268 holds inline. Chosen, no evidence names them: Find, IsFim, m_registros, m_corrente, m_nome.
// Add(KeyType, RecordType) has no record: its body is fn 5377's. src/units/113-uenux2-cdatamap.mk lists what the
// bytes decide and what they do not.
#pragma once

#include <format>
#include <map>
#include <string>

#include "api/io/eueioerror.h"

namespace api {

template <typename KeyType, typename RecordType>
class CDataMap {
public:
    using Container = std::map<KeyType, RecordType>;

    CDataMap() = default;
    explicit CDataMap(const std::string& nome) : m_corrente(m_registros.end()), m_nome(nome) {}

    bool IsFim() const { return m_corrente == m_registros.end(); }

    // (original lines 30-94: content not recovered)
#line 95
    RecordType* GetCurrent() const
    {
        if (m_corrente == m_registros.end()) {
            throw CUeIoError(EUE_IO_REGISTRO_CORRENTE_INVALIDO, std::format("O registro corrente estava inválido {}", m_nome));
        }
        return &m_corrente->second;
    }

    // (original lines 103-113: content not recovered)
#line 114
    void Next()
    {
        if (m_corrente == m_registros.end()) {
            throw CUeIoError(EUE_IO_OPERACAO_INVALIDA, std::format("Operação inválida {}", m_nome));
        }
        ++m_corrente;
    }

    // (original lines 122-137: content not recovered)
#line 138
    void Add(const KeyType& chave, const RecordType& registro) { Add(typename Container::value_type(chave, registro)); }

    void Add(const typename Container::value_type& registro)
    {
        if (m_registros.find(registro.first) != m_registros.end()) {
            throw CUeIoError(EUE_IO_REGISTRO_DUPLICADO, std::format("Duplicidade de registro {}", m_nome));
        }
        m_corrente = m_registros.insert(registro).first;
    }

    // (original lines 148-153: content not recovered)
#line 154
    void Update(const KeyType& chave, const RecordType& registro)
    {
        const typename Container::iterator it = m_registros.find(chave);
        if (it == m_registros.end()) {
            throw CUeIoError(EUE_IO_REGISTRO_NAO_ENCONTRADO, std::format("Registro não encontrado {}", m_nome));
        }
        it->second = registro;
        m_corrente = it;
    }

    RecordType* Find(const KeyType& chave)
    {
        const typename Container::iterator it = m_registros.find(chave);
        if (it == m_registros.end()) {
            return nullptr;
        }
        m_corrente = it;
        return &it->second;
    }

private:
    Container m_registros;
    typename Container::iterator m_corrente;
    std::string m_nome;
};

} // namespace api
