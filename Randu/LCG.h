#pragma once

class LCG
{
	int m_a;
	unsigned long long  m_seed;
	unsigned long long m_modulus;
public:
	LCG(int a, unsigned long long  seed, unsigned long long  modulus) : m_a(a), m_seed(seed), m_modulus(modulus) {};
	LCG& operator ++ (int);
	unsigned long long operator* () {  return m_seed; }


};

