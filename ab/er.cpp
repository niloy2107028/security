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

    int y = bme(g, x, p);

    cout << "public key (p, g, y): "
         << p << " " << g << " " << y << endl;

    cout << "private key x = " << x << endl;

    // message and original random value
    int m = 20;
    int k = 7;

    // original encryption
    int c1 = bme(g, k, p);

    int c2 = (m * bme(y, k, p)) % p;

    cout << "original cipher = ("
         << c1 << ", " << c2 << ")" << endl;

    // new random value for rerandomization
    int k2 = 9;

    // rerandomization
    int c1_new = (c1 * bme(g, k2, p)) % p;

    int c2_new = (c2 * bme(y, k2, p)) % p;

    cout << "re-randomized cipher = ("
         << c1_new << ", " << c2_new << ")" << endl;

    // decryption
    int s = bme(c1_new, x, p);

    int s_inv = modinv(s, p);

    int decrypted = (c2_new * s_inv) % p;

    cout << "decrypted message = " << decrypted << endl;

    cout << "expected = " << m << endl;

    if (decrypted == m)
    {
        cout << "message is same" << endl;
    }
    else
    {
        cout << "message is not same" << endl;
    }

    return 0;
}