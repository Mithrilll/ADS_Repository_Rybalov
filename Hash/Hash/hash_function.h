#pragma once

class IHashFunction
{
public:
	virtual unsigned int operator()(unsigned int, unsigned int, unsigned int) = 0;
};

class FirstHashFunction : public IHashFunction
{
public:
	unsigned int operator()(unsigned int N, unsigned int K, unsigned int i) override
	{
		if (i == 0)
			return K % N;
		else if (i > 0)
			return (operator()(N, K, i - 1) + c * i + d * i * i) % N;
	}

private:
	const int c = 5;
	const int d = 3;
};

class FirstHashFunction : public IHashFunction
{
public:
	unsigned int operator()(unsigned int N, unsigned int K, unsigned int i) override
	{
		if (i == 0)
			return K % N;
		else if (i > 0)
			return static_cast<unsigned int>(operator()(N, K, i - 1) * a * N) % N;
	}

private:
	const double a = 0.6180339887;
};