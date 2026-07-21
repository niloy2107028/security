#include <iostream>
using namespace std;

// Find GCD
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Calculate (base^exp) % mod
int power(int base, int exp, int mod)
{
    int result = 1;

    for (int i = 0; i < exp; i++)
    {
        result = (result * base) % mod;
    }

    return result;
}

int main()
{
    int p, q;

    cout << "Enter two prime numbers: ";
    cin >> p >> q;

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    cout << "n = " << n << endl;
    cout << "phi = " << phi << endl;

    // Find e
    int e = 2;
    while (gcd(e, phi) != 1)
    {
        e++;
    }

    // Find d
    int d = 1;
    while ((d * e) % phi != 1)
    {
        d++;
    }

    cout << "Public Key : (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;

    int message;

    cout << "Enter message: ";
    cin >> message;

    int cipher = power(message, e, n);

    cout << "Encrypted = " << cipher << endl;

    int decrypted = power(cipher, d, n);

    cout << "Decrypted = " << decrypted << endl;

    return 0;
}