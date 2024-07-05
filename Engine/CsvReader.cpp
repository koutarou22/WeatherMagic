//#include "csvReader.h"
//#include <fstream>
//#include <assert.h>
//
//CsvReader::CsvReader()
//{
//}
//
//CsvReader::CsvReader(std::string filename)
//{
//	Load(filename);
//}
//
//bool CsvReader::Load(std::string filename)
//{
//	all.clear();
//
//	std::ifstream ifs(filename);
//	if (!ifs) return false;
//
//	// BOM Skipする
//	unsigned char BOMS[] = { 0xEF, 0xBB, 0xBF };
//	bool found = true;
//	for (int i = 0; i < 3; i++) {
//		if (ifs.get() != BOMS[i]) {
//			found = false;
//			break;
//		}
//	}
//	if (!found) {
//		ifs.seekg(std::ios_base::beg);
//	}
//
//	// データを読む
//	std::string lineStr;
//	while (getline(ifs, lineStr)) {
//		while (true) {
//			int dq = 0;
//			for (int i = 0; i < lineStr.size(); i++) {
//				if (lineStr[i] == '"')
//					dq++;
//			}
//			if (dq % 2 == 0)
//				break;
//			std::string s;
//			getline(ifs, s);
//			lineStr += "\n" + s;
//		}
//		for (auto it = lineStr.begin(); it != lineStr.end();) {
//			if (*it == '"')
//				it = lineStr.erase(it);
//			if (it != lineStr.end())
//				it++;
//		}
//
//		// 行内を,で切り分ける
//		LINEREC lineRecord;
//		int top = 0;
//		bool indq = false;
//		for (int n = 0; n < lineStr.size(); n++) {
//			if (lineStr[n] == ',') {
//				if (!indq) {
//					lineRecord.record.emplace_back(lineStr.substr(top, (size_t)(n - top)));
//					top = n + 1;
//				}
//			}
//			else if (lineStr[n] == '"')
//				indq = !indq;
//		}
//		lineRecord.record.emplace_back(lineStr.substr(top, lineStr.size() - top));
//		all.emplace_back(lineRecord);
//	}
//	ifs.close();
//	return true;
//}
//
//CsvReader::~CsvReader()
//{
//	for (auto rec : all)
//		rec.record.clear();
//	all.clear();
//}
//
//int CsvReader::GetHeight()
//{
//	return all.size();
//}
//
//int CsvReader::GetWidth(int line)
//{
//	assert(line < GetHeight());
//	return all[line].record.size();
//}
//
//std::string CsvReader::GetString(int column, int line)
//{
//	assert(line < GetHeight());
//	if (column >= GetWidth(line))
//		return "";
//	return all[line].record[column];
//}
//
//int CsvReader::GetInt(int column, int line)
//{
//	std::string str = GetString(column, line);
//	if (str == "")
//		return 0;
//	return std::stoi(str);
//}
//
//float CsvReader::GetFloat(int column, int line)
//{
//	std::string str = GetString(column, line);
//	if (str == "")
//		return 0.0f;
//	return std::stof(str);
//}
#include <Windows.h>
#include "CsvReader.h"
#include<assert.h>


//コンストラクタ
CsvReader::CsvReader()
{
	data_.clear();
}

//デストラクタ
CsvReader::~CsvReader()
{
	//全データを開放
	for (int y = 0; y < data_.size(); y++)
	{
		for (int x = 0; x < data_[y].size(); x++)
		{
			data_[y][x].clear();
		}
	}
}

//CSVファイルのロード
bool CsvReader::Load(std::string fileName)
{
	//ファイルを開く
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//開けなかった
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::string message = "「" + fileName + "」が開けません。\n開いている場合は閉じてください。";
		MessageBox(NULL, message.c_str(), "BaseProjDx9エラー", MB_OK);

		return false;
	}

	//ファイルのサイズ（文字数）を調べる
	DWORD fileSize = GetFileSize(hFile, NULL);

	//すべての文字を入れられる配列を用意
	char* temp;
	temp = new char[fileSize];

	//ファイルの中身を配列に読み込む
	DWORD dwBytes = 0;
	ReadFile(hFile, temp, fileSize, &dwBytes, NULL);

	//開いたファイルを閉じる
	CloseHandle(hFile);

	//1行のデータを入れる配列
	std::vector<std::string>	line;

	//調べる文字の位置
	DWORD index = 0;

	//最後の文字まで繰り返す
	while (index < fileSize)
	{
		//index文字目から「,」か「改行」までの文字列を取得
		std::string val;
		GetToComma(&val, temp, &index);

		//文字数が0だったということは行末
		if (val.length() - 1 == 0)
		{
			//_dataに1行分追加
			data_.push_back(line);

			//1行データをクリア
			line.clear();

			//index++;
			continue;
		}

		//1行分のデータに追加
		line.push_back(val);
	}

	//読み込んだデータは開放する
	delete[] temp;

	//成功
	return true;
}

//「,」か「改行」までの文字列を取得
void CsvReader::GetToComma(std::string* result, std::string data, DWORD* index)
{
	//「,」まで一文字ずつresultに入れる
	while (data[*index] != ',' && data[*index] != '\n' && data[*index] != '\r')
	{
		*result += data[*index];
		(*index)++;
	}

	//最後に「\0」を付ける
	*result += '\0';
	(*index)++;
}

//指定した位置のデータを文字列で取得
std::string CsvReader::GetString(DWORD x, DWORD y)
{
	if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
		return "";

	return data_[y][x];
}

//指定した位置のデータを整数で取得
int CsvReader::GetValue(DWORD x, DWORD y)
{
	return atoi(GetString(x, y).c_str());
}

//ファイルの列数を取得
size_t CsvReader::GetWidth()
{
	return data_[0].size();

}

//ファイルの行数を取得
size_t CsvReader::GetHeight()
{
	return data_.size();
}

//std::string CsvReader::GetString(int column, int line)
//{
//	assert(line < GetHeight());
//	if (column >= GetWidth(line))
//		return "";
//	return all[line].record[column];
//}

int CsvReader::GetInt(int column, int line)
{
	std::string str = GetString(column, line);
	if (str == "")
		return 0;
	return std::stoi(str);
}

float CsvReader::GetFloat(int column, int line)
{
	std::string str = GetString(column, line);
	if (str == "")
		return 0.0f;
	return std::stof(str);
}

//int CsvReader::GetWidth(int line)
//{
//	assert(line < GetHeight());
//	return all[line].record.size();
//}

