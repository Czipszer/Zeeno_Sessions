# BigInt

Implement class allowing integer airthmetic operations with unlimited precision.

1. Create a class with constructors taking
    - `std::uint64_t`
    - `std::string`
    - `void` - implicit constructor
    - `const BigInt&` - copy constructor
1. Implement non-member output stream operator
    - `std::ostream& operator<<(std::ostream& os, const BigInt& big);`
1. Implement `operator==`
1. Implement `operator* (int)` to multiply the BigInt by a number. This number will be always `3` and you do not have to test it for other values.
1. Implement modulo operator `operator% (int)` to get the remainder after division. `12 % 5 = 2`. The parameter will be always `2` to test whether the number is odd or even.
1. Implement minus operator `operator- (int)`. The parameter will always be `1`
1. Implement division. `operator/(int)`. The parameter will always be `2`.
1. Test the code by replacing the implementation of BigInt in the `./zeeno/big-int`.