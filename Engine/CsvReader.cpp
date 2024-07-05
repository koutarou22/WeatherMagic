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
//	// BOM Skip����
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
//	// �f�[�^��ǂ�
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
//		// �s����,�Ő؂蕪����
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


//�R���X�g���N�^
CsvReader::CsvReader()
{
	data_.clear();
}

//�f�X�g���N�^
CsvReader::~CsvReader()
{
	//�S�f�[�^���J��
	for (int y = 0; y < data_.size(); y++)
	{
		for (int x = 0; x < data_[y].size(); x++)
		{
			data_[y][x].clear();
		}
	}
}

//CSV�t�@�C���̃��[�h
bool CsvReader::Load(std::string fileName)
{
	//�t�@�C�����J��
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//�J���Ȃ�����
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::string message = "�u" + fileName + "�v���J���܂���B\n�J���Ă���ꍇ�͕��Ă��������B";
		MessageBox(NULL, message.c_str(), "BaseProjDx9�G���[", MB_OK);

		return false;
	}

	//�t�@�C���̃T�C�Y�i�������j�𒲂ׂ�
	DWORD fileSize = GetFileSize(hFile, NULL);

	//���ׂĂ̕�����������z���p��
	char* temp;
	temp = new char[fileSize];

	//�t�@�C���̒��g��z��ɓǂݍ���
	DWORD dwBytes = 0;
	ReadFile(hFile, temp, fileSize, &dwBytes, NULL);

	//�J�����t�@�C�������
	CloseHandle(hFile);

	//1�s�̃f�[�^������z��
	std::vector<std::string>	line;

	//���ׂ镶���̈ʒu
	DWORD index = 0;

	//�Ō�̕����܂ŌJ��Ԃ�
	while (index < fileSize)
	{
		//index�����ڂ���u,�v���u���s�v�܂ł̕�������擾
		std::string val;
		GetToComma(&val, temp, &index);

		//��������0�������Ƃ������Ƃ͍s��
		if (val.length() - 1 == 0)
		{
			//_data��1�s���ǉ�
			data_.push_back(line);

			//1�s�f�[�^���N���A
			line.clear();

			//index++;
			continue;
		}

		//1�s���̃f�[�^�ɒǉ�
		line.push_back(val);
	}

	//�ǂݍ��񂾃f�[�^�͊J������
	delete[] temp;

	//����
	return true;
}

//�u,�v���u���s�v�܂ł̕�������擾
void CsvReader::GetToComma(std::string* result, std::string data, DWORD* index)
{
	//�u,�v�܂ňꕶ������result�ɓ����
	while (data[*index] != ',' && data[*index] != '\n' && data[*index] != '\r')
	{
		*result += data[*index];
		(*index)++;
	}

	//�Ō�Ɂu\0�v��t����
	*result += '\0';
	(*index)++;
}

//�w�肵���ʒu�̃f�[�^�𕶎���Ŏ擾
std::string CsvReader::GetString(DWORD x, DWORD y)
{
	if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
		return "";

	return data_[y][x];
}

//�w�肵���ʒu�̃f�[�^�𐮐��Ŏ擾
int CsvReader::GetValue(DWORD x, DWORD y)
{
	return atoi(GetString(x, y).c_str());
}

//�t�@�C���̗񐔂��擾
size_t CsvReader::GetWidth()
{
	return data_[0].size();

}

//�t�@�C���̍s�����擾
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

