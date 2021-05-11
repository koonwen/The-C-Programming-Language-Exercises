unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned dropbits(unsigned x, int n)
{
  return x & (~0 << n);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned _x = getbits(x, p, n);
  unsigned _y = dropbits(y, n);
  return _x | _y;    
}
