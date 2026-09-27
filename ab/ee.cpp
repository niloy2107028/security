#include <iostream>
using namespace std;

// Binary Modular Exponentiation
int bme(int a, int e, int m)
{
    int r = 1;
    a = a % m;

    while (e)
    {
        if (e & 1)
            r = r * a % m;

        a = a * a % m;
        e >>= 1;
    }

    return r;
}

// Extended Euclidean Algorithm
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

// Modular Inverse
int modinv(int a, int m)
{
    int x, y;
    int g = eea(a, m, x, y);

    if (g != 1)
        // mod inverse only exist when gcd(a,m)=1
        return -1;

    x = x % m;

    if (x < 0)
        x += m;

    return x;
}

// Find primitive root g
int findG(int p)
{
    for (int g = 2; g < p; g++)
    {
        bool used[p] = {false};
        int value = 1;

        for (int i = 1; i < p; i++)
        {
            value = (value * g) % p;

            if (used[value])
                break;

            used[value] = true;
        }

        bool ok = true;

        for (int i = 1; i < p; i++)
        {
            if (!used[i])
            {
                ok = false;
                break;
            }
        }

        if (ok)
            return g;
    }

    return -1;
}

int main()
{
    int p, x, m, k;

    // Input p
    cout << "Enter prime p: ";
    cin >> p;

    // Calculate g
    int g = findG(p);

    cout << "Primitive root g = " << g << endl;

    // Private key
    cout << "Enter private key x: ";
    cin >> x;

    // Public key
    int y = bme(g, x, p);

    cout << "Public key = (" << p << ", " << g << ", " << y << ")" << endl;

    // Message
    cout << "Enter message m: ";
    cin >> m;

    // Random k
    cout << "Enter random k: ";
    cin >> k;

    // ---------------- ENCRYPTION ----------------

    int c1 = bme(g, k, p);

    int c2 = (m * bme(y, k, p)) % p;

    cout << "\nEncryption:" << endl;
    cout << "C1 = " << c1 << endl;
    cout << "C2 = " << c2 << endl;

    // ---------------- DECRYPTION ----------------

    int s = bme(c1, x, p);

    int s_inv = modinv(s, p);

    int decrypted = (c2 * s_inv) % p;

    cout << "\nDecryption:" << endl;
    cout << "S = " << s << endl;
    cout << "S^-1 = " << s_inv << endl;
    cout << "Decrypted message = " << decrypted << endl;

    // Check
    cout << "\nResult: ";

    if (m == decrypted)
        cout << "Message is SAME" << endl;
    else
        cout << "Message is NOT SAME" << endl;

    return 0;
}