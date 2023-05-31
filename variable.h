#pragma once 
#include <variant>
#include <string>
#include "hash_set.h"
class variable
{
protected:
    enum TYPE{
        INTEGER,
        HASH
    };

    std::string name;
    std::variant<int, hash_set> value;
    TYPE type;
public:
    template<typename Str,
        typename Ty, typename = std::enable_if_t<
                                            std::is_constructible_v<std::variant<int, hash_set>,  std::remove_reference_t<Ty>>
                                        >>
    variable(Str&& name, Ty&& val) : name(std::forward<Str>(name)), value(std::forward<Ty>(val)) {
        if (std::is_same_v<std::remove_reference_t<Ty>, int>) {
            type = INTEGER;
        } else {
            type = HASH;
        }
    }

    const std::string& get_name() const noexcept { return name; }

    friend std::ostream& operator<<(std::ostream&, const variable&);

    ~variable() {}
};

std::ostream& operator<<(std::ostream& os, const variable& var) {
    os << "name: " << var.name << " "<< std::endl;
    if (var.type == variable::HASH) {
        os << std::get<hash_set>(var.value);
    } else {
        os << std::get<int>(var.value);
    }
    return os;
}


