#include <Novice.h>
#include <math.h>
#include <assert.h>

const char kWindowTitle[] = "LE2D_20_フルヤユウト";

struct Matrix4x4 {
	float m[4][4];
};

// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = m1.m[row][col] + m2.m[row][col];
		}
	}
	return result;
}

// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = m1.m[row][col] - m2.m[row][col];
		}
	}
	return result;
}

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			for (int k = 0; k < 4; ++k) {
				result.m[row][col] += m1.m[row][k] * m2.m[k][col];
			}
		}
	}
	return result;
}

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result = {};
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = m.m[col][row];
		}
	}
	return result;
}

// 単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; ++i) {
		result.m[i][i] = 1.0f;
	}
	return result;
}
// 4x4行列の逆行列（長文実装）
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;

	float a2323 = m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2];
	float a1323 = m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1];
	float a1223 = m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1];
	float a0323 = m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0];
	float a0223 = m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0];
	float a0123 = m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0];

	float a2313 = m.m[1][2] * m.m[3][3] - m.m[1][3] * m.m[3][2];
	float a1313 = m.m[1][1] * m.m[3][3] - m.m[1][3] * m.m[3][1];
	float a1213 = m.m[1][1] * m.m[3][2] - m.m[1][2] * m.m[3][1];
	float a2312 = m.m[1][2] * m.m[2][3] - m.m[1][3] * m.m[2][2];
	float a1312 = m.m[1][1] * m.m[2][3] - m.m[1][3] * m.m[2][1];
	float a1212 = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
	float a0313 = m.m[1][0] * m.m[3][3] - m.m[1][3] * m.m[3][0];
	float a0213 = m.m[1][0] * m.m[3][2] - m.m[1][2] * m.m[3][0];
	float a0312 = m.m[1][0] * m.m[2][3] - m.m[1][3] * m.m[2][0];
	float a0212 = m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0];
	float a0113 = m.m[1][0] * m.m[3][1] - m.m[1][1] * m.m[3][0];
	float a0112 = m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0];

	result.m[0][0] = +m.m[1][1] * a2323 - m.m[1][2] * a1323 + m.m[1][3] * a1223;
	result.m[0][1] = -m.m[0][1] * a2323 + m.m[0][2] * a1323 - m.m[0][3] * a1223;
	result.m[0][2] = +m.m[0][1] * a2313 - m.m[0][2] * a1313 + m.m[0][3] * a1213;
	result.m[0][3] = -m.m[0][1] * a2312 + m.m[0][2] * a1312 - m.m[0][3] * a1212;

	result.m[1][0] = -m.m[1][0] * a2323 + m.m[1][2] * a0323 - m.m[1][3] * a0223;
	result.m[1][1] = +m.m[0][0] * a2323 - m.m[0][2] * a0323 + m.m[0][3] * a0223;
	result.m[1][2] = -m.m[0][0] * a2313 + m.m[0][2] * a0313 - m.m[0][3] * a0213;
	result.m[1][3] = +m.m[0][0] * a2312 - m.m[0][2] * a0312 + m.m[0][3] * a0212;

	result.m[2][0] = +m.m[1][0] * a1323 - m.m[1][1] * a0323 + m.m[1][3] * a0123;
	result.m[2][1] = -m.m[0][0] * a1323 + m.m[0][1] * a0323 - m.m[0][3] * a0123;
	result.m[2][2] = +m.m[0][0] * a1313 - m.m[0][1] * a0313 + m.m[0][3] * a0113;
	result.m[2][3] = -m.m[0][0] * a1312 + m.m[0][1] * a0312 - m.m[0][3] * a0112;

	result.m[3][0] = -m.m[1][0] * a1223 + m.m[1][1] * a0223 - m.m[1][2] * a0123;
	result.m[3][1] = +m.m[0][0] * a1223 - m.m[0][1] * a0223 + m.m[0][2] * a0123;
	result.m[3][2] = -m.m[0][0] * a1213 + m.m[0][1] * a0213 - m.m[0][2] * a0113;
	result.m[3][3] = +m.m[0][0] * a1212 - m.m[0][1] * a0212 + m.m[0][2] * a0112;

	// 行列式（det）を求める
	float det =
		m.m[0][0] * result.m[0][0] +
		m.m[0][1] * result.m[1][0] +
		m.m[0][2] * result.m[2][0] +
		m.m[0][3] * result.m[3][0];

	assert(det != 0.0f); // det が 0 の場合、逆行列は存在しない

	// 逆行列 = adjugate / det
	float invDet = 1.0f / det;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] *= invDet;
		}
	}
	return result;
}

// --- 描画用関数 ---
static const int kColumnWidth = 60;
static const int kRowHeight = 20;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth,
				y + (row + 1) * kRowHeight,
				"%6.02f", matrix.m[row][column]
			);
		}
	}
}

// --- メイン関数 ---
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Novice::Initialize(kWindowTitle, 1280, 720);

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Matrix4x4 v1{ {
		{3.2f, 0.7f, 9.6f, 4.4f},
		{5.5f, 1.3f, 7.8f, 2.1f},
		{6.9f, 8.0f, 2.6f, 1.0f},
		{0.5f, 7.2f, 5.1f, 3.3f}
	} };

	Matrix4x4 v2{ {
		{4.1f, 6.5f, 3.3f, 2.2f},
		{8.8f, 0.6f, 9.9f, 7.7f},
		{1.1f, 5.5f, 6.6f, 0.0f},
		{3.3f, 9.9f, 8.8f, 2.2f}
	} };

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();

		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		Matrix4x4 resultAdd = Add(v1, v2);
		Matrix4x4 resultSubtract = Subtract(v1, v2);
		Matrix4x4 resultMultiply = Multiply(v1, v2);
		Matrix4x4 inverseM1 = Inverse(v1);
		Matrix4x4 inverseM2 = Inverse(v2);
		Matrix4x4 transposeM1 = Transpose(v1);
		Matrix4x4 transposeM2 = Transpose(v2);
		Matrix4x4 identity = MakeIdentity4x4();

		// 描画
		MatrixScreenPrintf(0, 0, resultAdd, "Add");
		MatrixScreenPrintf(0, kRowHeight * 6, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 12, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 18, inverseM1, "inverseM1");
		MatrixScreenPrintf(0, kRowHeight * 24, inverseM2, "inverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "transposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 6, transposeM2, "transposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 12, identity, "identity");

		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}
