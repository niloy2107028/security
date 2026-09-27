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

    int x = 127;

    // public key
    int y = bme(g, x, p);

    cout << "public key (p, g, y): "
         << p << " " << g << " " << y << endl;

    cout << "private key x = " << x << endl;

    // message
    int m;

    cout << "enter message: ";
    cin >> m;

    // random value
    int k = 5;

    if (__gcd(k, p - 1) != 1)
    {
        cout << "k is not coprime to p-1" << endl;
        return 0;
    }

    // signature generation
    int y1 = bme(g, k, p);

    int k_inv = modinv(k, p - 1);

    int y2 = (k_inv * (m - x * y1)) % (p - 1);

    if (y2 < 0)
    {
        y2 += (p - 1);
    }

    cout << "signature (y1, y2) = ("
         << y1 << ", " << y2 << ")" << endl;

    // signature verification
    int left = bme(g, m, p);

    int right =
        (bme(y, y1, p) * bme(y1, y2, p)) % p;

    cout << "left = " << left << endl;
    cout << "right = " << right << endl;

    if (left == right)
    {
        cout << "signature valid" << endl;
    }
    else
    {
        cout << "signature invalid" << endl;
    }

    return 0;
}