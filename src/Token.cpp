//
// Created by robert on 19.04.2020.
//

#include "../include/Token.h"

bool operator==(const Token &lhs, const Token &rhs) {
    return lhs.value == rhs.value && typeid(rhs) == typeid(lhs);
}

bool operator!=(const Token &lhs, const Token &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &out, const Token& t) {
    return out << t.value << " " << t.type << " " << "position is: "
            << t.position.row << ": " << t.position.column << '\n';
}

