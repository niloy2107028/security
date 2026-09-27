#include <bits/stdc++.h>

using namespace std;

// binary modular exponentiation
int bme(int a, int e, int m)
{
    int r = 1;
    a = a % m;

    while (e)
    {
        if (e & 1)
        {
            r = r * a % m;
        }

        a = a * a % m;
        e >>= 1;
    }

    return r;
}

// extended euclidean algorithm
int eea(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = eea(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

// modular inverse
int modinv(int a, int m)
{
    int x, y;

    int g = eea(a, m, x, y);

    if (g != 1)
    {
        return -1;
    }

    x = x % m;

    if (x < 0)
    {
        x += m;
    }

    return x;
}

// find primitive root g
int findg(int p)
{
    for (int g = 2; g < p; g++)
    {
        bool rem[p] = {false};
        int value = 1;

        for (int i = 1; i < p; i++)
        {
            value = (value * g) % p;

            if (rem[value])
            {
                break;
            }

            rem[value] = true;
        }

        bool ok = true;

        for (int i = 1; i < p; i++)
        {
            if (!rem[i])
            {
                ok = false;
                break;
            }
        }

        if (ok)
        {
            return g;
        }
    }

    return -1;
}

int main()
{
    // key generation
    int p = 467;
    int g = findg(p);

    if (g == -1)
    {
        cout << "no primitive root found" << endl;
        return 0;
    }

    int x = 123;

    // public key
    int y = bme(g, x, p);

    cout << "public key (p, g, y): "
         << p << " " << g << " " << y << endl;

    cout << "private key x = " << x << endl;

    // two messages
    int m1 = 5;
    int m2 = 9;

    int k1 = 7;
    int k2 = 11;

    // encrypt m1
    int c11 = bme(g, k1, p);

    int c12 = (m1 * bme(y, k1, p)) % p;

    // encrypt m2
    int c21 = bme(g, k2, p);

    int c22 = (m2 * bme(y, k2, p)) % p;

    cout << "cipher 1 = (" << c11 << ", " << c12 << ")" << endl;

    cout << "cipher 2 = (" << c21 << ", " << c22 << ")" << endl;

    // product cipher
    int c1p = (c11 * c21) % p;

    int c2p = (c12 * c22) % p;

    cout << "combined cipher = ("
         << c1p << ", " << c2p << ")" << endl;

    // decryption
    int s = bme(c1p, x, p);

    int s_inv = modinv(s, p);

    int decrypted = (c2p * s_inv) % p;

    cout << "decrypted product = " << decrypted << endl;

    cout << "expected = " << (m1 * m2) % p << endl;

    if (decrypted == (m1 * m2) % p)
    {
        cout << "product cipher works!" << endl;
    }
    else
    {
        cout << "invalid!" << endl;
    }

    return 0;
}