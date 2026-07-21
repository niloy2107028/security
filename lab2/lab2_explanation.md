# Binary Exponentiation 

Let's trace the function with a complete example.

We'll calculate:

```
4^13 mod 33
```

So,

```cpp
mod_pow(4, 13, 33);
```

Initial values:

```
a = 4
e = 13
m = 33
r = 1
```

---

# Initial Step

```cpp
int64 r = 1;
```

```
r = 1
```

---

```cpp
a %= m;
```

```
a = 4 % 33 = 4
```

No change because 4 is already less than 33.

---

# Iteration 1

Current values

```
a = 4
e = 13
r = 1
```

### Check

```cpp
if (e & 1)
```

Binary of 13

```
13 = 1101₂
```

Last bit is **1**, so **13 is odd**.

Condition is **true**.

---

### Update r

```cpp
r = r * a % m;
```

```
r = 1 × 4 % 33

=4
```

Now

```
r = 4
```

---

### Square a

```cpp
a = a * a % m;
```

```
a = 4 × 4 %33

=16
```

Now

```
a =16
```

---

### Divide exponent by 2

```cpp
e >>=1;
```

```
13/2

=6
```

Now

```
e =6
```

---

Current values

| a  | e | r |
| -- | - | - |
| 16 | 6 | 4 |

---

# Iteration 2

Current

```
a=16

e=6

r=4
```

Binary

```
6

110₂
```

Even

```cpp
if(e&1)
```

False

So

```
r remains 4
```

---

Square a

```
16²

=256

256 mod33

=25
```

Now

```
a=25
```

---

Divide exponent

```
6/2

=3
```

Now

```
e=3
```

---

Current values

| a  | e | r |
| -- | - | - |
| 25 | 3 | 4 |

---

# Iteration 3

Current

```
a=25

e=3

r=4
```

Binary

```
3

11₂
```

Odd

Condition true.

---

Update r

```
4×25

=100

100 mod33

=1
```

Now

```
r=1
```

---

Square a

```
25²

625

625 mod33

=31
```

Now

```
a=31
```

---

Divide exponent

```
3/2

=1
```

Now

```
e=1
```

---

Current values

| a  | e | r |
| -- | - | - |
| 31 | 1 | 1 |

---

# Iteration 4

Current

```
a=31

e=1

r=1
```

Odd

Condition true.

---

Update r

```
1×31

=31

31 mod33

=31
```

Now

```
r=31
```

---

Square a

```
31²

961

961 mod33

=4
```

Now

```
a=4
```

---

Divide exponent

```
1/2

=0
```

Now

```
e=0
```

Loop stops.

---

Return

```cpp
return r;
```

Output

```
31
```

---

# Verification

Normal calculation

```
4¹³

=67,108,864
```

Now

```
67,108,864 mod33

=31
```

Exactly the same answer.

---

# Why is this algorithm fast?

### Normal Method

To calculate

```
4¹³
```

you would multiply

```
4×4×4×4×4×4×4×4×4×4×4×4×4
```

**13 multiplications**.

---

### Fast Method (`mod_pow`)

It repeatedly:

* Squares the base (`a = a × a`)
* Halves the exponent (`e >>= 1`)
* Multiplies into the answer only when the exponent is odd

So for `e = 13`, it performs only **4 loop iterations** instead of 13 multiplications.

---

# Complete Trace Table

| Iteration |  e | Odd? |      r |  a |
| --------- | -: | :--: | -----: | -: |
| Start     | 13 |   -  |      1 |  4 |
| 1         | 13 |  Yes |      4 | 16 |
| 2         |  6 |  No  |      4 | 25 |
| 3         |  3 |  Yes |      1 | 31 |
| 4         |  1 |  Yes |     31 |  4 |
| End       |  0 |   -  | **31** |  - |

**Final Answer:**

```
mod_pow(4, 13, 33) = 31
```

This algorithm is called **Binary Exponentiation** (also known as **Fast Modular Exponentiation**) because it processes the exponent one binary bit at a time, making its time complexity **O(log₂ e)** instead of **O(e)**.

---

That's because you're jumping into **Extended Euclidean Algorithm** before understanding the math behind it.

Forget the code for a moment.

---

## What do we want in RSA?

We want to find `d` such that

```
e * d mod φ = 1
```

This is our only goal.

---

## How can we find `d`?

Mathematicians proved that if

```
gcd(e, φ) = 1
```

then there exist two integers `x` and `y` such that

```
e * x + φ * y = 1
```

This is called **Bézout's Identity**.

Notice that **we are not choosing `x` and `y` ourselves**.

The **Extended Euclidean Algorithm (`egcd`) automatically finds them**.

---

## Why is `x` useful?

Look at this equation:

```
e * x + φ * y = 1
```

Take modulo `φ` on both sides.

```
(e * x + φ * y) mod φ = 1
```

Since any multiple of `φ` becomes `0` modulo `φ`,

```
φ * y mod φ = 0
```

So the equation becomes

```
e * x mod φ = 1
```

Now compare it with what RSA needs:

```
e * d mod φ = 1
```

They are exactly the same equation.

So,

```
d = x
```

---

## So what is `y`?

It is **just another number** required to satisfy

```
e * x + φ * y = 1
```

After taking modulo `φ`, `y` disappears because

```
φ * y mod φ = 0
```

So RSA never uses `y`.

---

## Think of `egcd()` as a black box

```
Input:
e, φ

        │
        ▼

egcd()

        │
        ▼

Output:
x, y
```

The algorithm guarantees:

```
e * x + φ * y = 1
```

From this mathematical property, we immediately know:

```
e * x mod φ = 1
```

Therefore,

```
d = x
```

---

### The important thing to realize

You **do not derive `x` yourself**.

The entire purpose of the **Extended Euclidean Algorithm** is to **compute `x` and `y`**. Once it returns them, the mathematics guarantees that `x` is the modular inverse, so RSA simply sets:

```cpp
d = x;
```

**Can I ask one question?**

Which part is confusing?

1. **Why does `egcd()` return `x` and `y`?**
2. **How does `egcd()` actually calculate `x` and `y` recursively?**
3. **Why does `x` become the modular inverse after taking modulo?**

These are three different concepts, and identifying which one is unclear will let me explain exactly that part.

---


Let's trace the function with a complete example.

We'll calculate:

```
4^13 mod 33
```

So we call:

```cpp
mod_pow(4, 13, 33);
```

### Initial Values

```
a = 4
e = 13
m = 33
r = 1
```

---

# Initial Step

```cpp
int64 r = 1;
```

```
r = 1
```

---

```cpp
a %= m;
```

```
a = 4 % 33 = 4
```

No change because `4 < 33`.

---

# Iteration 1

Current values:

```
a = 4
e = 13
r = 1
```

### Check

```cpp
if (e & 1)
```

Binary of 13:

```
13 = 1101₂
```

The last bit is **1**, so **13 is odd**.

Condition is **true**.

---

### Update `r`

```cpp
r = r * a % m;
```

```
r = 1 × 4 % 33
  = 4
```

Now:

```
r = 4
```

---

### Square `a`

```cpp
a = a * a % m;
```

```
a = 4 × 4 % 33
  = 16
```

Now:

```
a = 16
```

---

### Divide the exponent by 2

```cpp
e >>= 1;
```

```
13 / 2 = 6
```

Now:

```
e = 6
```

---

Current values:

| a | e | r |
|---:|---:|---:|
| 16 | 6 | 4 |

---

# Iteration 2

Current values:

```
a = 16
e = 6
r = 4
```

Binary of 6:

```
6 = 110₂
```

Even.

```cpp
if (e & 1)
```

Condition is **false**.

So:

```
r remains 4
```

---

### Square `a`

```
16² = 256

256 mod 33 = 25
```

Now:

```
a = 25
```

---

### Divide the exponent

```
6 / 2 = 3
```

Now:

```
e = 3
```

---

Current values:

| a | e | r |
|---:|---:|---:|
| 25 | 3 | 4 |

---

# Iteration 3

Current values:

```
a = 25
e = 3
r = 4
```

Binary of 3:

```
3 = 11₂
```

Odd.

Condition is **true**.

---

### Update `r`

```
4 × 25 = 100

100 mod 33 = 1
```

Now:

```
r = 1
```

---

### Square `a`

```
25² = 625

625 mod 33 = 31
```

Now:

```
a = 31
```

---

### Divide the exponent

```
3 / 2 = 1
```

Now:

```
e = 1
```

---

Current values:

| a | e | r |
|---:|---:|---:|
| 31 | 1 | 1 |

---

# Iteration 4

Current values:

```
a = 31
e = 1
r = 1
```

Odd.

Condition is **true**.

---

### Update `r`

```
1 × 31 = 31

31 mod 33 = 31
```

Now:

```
r = 31
```

---

### Square `a`

```
31² = 961

961 mod 33 = 4
```

Now:

```
a = 4
```

---

### Divide the exponent

```
1 / 2 = 0
```

Now:

```
e = 0
```

The loop stops.

---

## Return

```cpp
return r;
```

Output:

```
31
```

---

# Verification

Normal calculation:

```
4¹³ = 67,108,864
```

Now:

```
67,108,864 mod 33 = 31
```

Exactly the same answer.

---

# Why is this algorithm fast?

### Normal Method

To calculate:

```
4¹³
```

you would multiply:

```
4 × 4 × 4 × 4 × 4 × 4 × 4 × 4 × 4 × 4 × 4 × 4 × 4
```

That requires **13 multiplications**.

---

### Fast Method (`mod_pow`)

It repeatedly:

- Squares the base (`a = a × a`)
- Halves the exponent (`e >>= 1`)
- Multiplies into the answer only when the exponent is odd

For `e = 13`, it performs only **4 loop iterations** instead of 13 multiplications.

---

# Complete Trace Table

| Iteration | e | Odd? | r | a |
|----------:|--:|:----:|--:|--:|
| Start | 13 | - | 1 | 4 |
| 1 | 13 | Yes | 4 | 16 |
| 2 | 6 | No | 4 | 25 |
| 3 | 3 | Yes | 1 | 31 |
| 4 | 1 | Yes | 31 | 4 |
| End | 0 | - | **31** | - |

---

## Final Answer

```
mod_pow(4, 13, 33) = 31
```

This algorithm is called **Binary Exponentiation** (also known as **Fast Modular Exponentiation**) because it processes the exponent one binary bit at a time, giving a time complexity of **O(log₂ e)** instead of **O(e)**.

---

# Understanding `x` and `y` in RSA

You're jumping into the **Extended Euclidean Algorithm** before understanding the math behind it.

Forget the code for a moment.

---

## What do we want in RSA?

We want to find `d` such that:

```
e × d mod φ = 1
```

This is our only goal.

---

## How can we find `d`?

Mathematicians proved that if:

```
gcd(e, φ) = 1
```

then there exist two integers `x` and `y` such that:

```
e × x + φ × y = 1
```

This is called **Bézout's Identity**.

Notice that **we are not choosing `x` and `y` ourselves**.

The **Extended Euclidean Algorithm (`egcd`) automatically finds them**.

---

## Why is `x` useful?

Start with:

```
e × x + φ × y = 1
```

Take modulo `φ` on both sides:

```
(e × x + φ × y) mod φ = 1
```

Since any multiple of `φ` becomes `0` modulo `φ`:

```
φ × y mod φ = 0
```

So the equation becomes:

```
e × x mod φ = 1
```

Compare it with RSA's requirement:

```
e × d mod φ = 1
```

They are exactly the same.

Therefore:

```
d = x
```

---

## So what is `y`?

It is simply another integer that satisfies:

```
e × x + φ × y = 1
```

After taking modulo `φ`, `y` disappears because:

```
φ × y mod φ = 0
```

So RSA never uses `y`.

---

## Think of `egcd()` as a black box

```
Input:
e, φ

      │
      ▼

   egcd()

      │
      ▼

Output:
x, y
```

The algorithm guarantees:

```
e × x + φ × y = 1
```

Therefore:

```
e × x mod φ = 1
```

So:

```
d = x
```

---

## The important thing to realize

You **do not derive `x` yourself**.

The entire purpose of the **Extended Euclidean Algorithm** is to compute `x` and `y`.

Once it returns them, mathematics guarantees that `x` is the modular inverse.

So RSA simply does:

```cpp
d = x;
```

---

# Where do these formulas come from?

These formulas are **not guessed**. They come directly from the Euclidean division equation.

Suppose:

```
a = q × b + r
```

where:

```
q = ⌊a / b⌋
r = a mod b
```

The recursive call has already found `x₁` and `y₁` such that:

```
b × x₁ + r × y₁ = gcd(a, b)
```

Replace `r` with `a - q × b`:

```
b × x₁ + (a - q × b) × y₁ = gcd(a, b)
```

Expand:

```
b × x₁ + a × y₁ - q × b × y₁ = gcd(a, b)
```

Group the `b` terms:

```
a × y₁ + b × (x₁ - q × y₁) = gcd(a, b)
```

Compare this with the desired form:

```
a × x + b × y = gcd(a, b)
```

Therefore:

```
x = y₁
```

and

```
y = x₁ - q × y₁
```

Since:

```
q = ⌊a / b⌋
```

the code becomes:

```cpp
x = y1;
y = x1 - (a / b) * y1;
```
