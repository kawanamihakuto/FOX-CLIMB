#include<string>
#include<fstream>
#include<sstream>

int main()
{
	std::string str_buf;
	std::string str_conma_buf;
	std::string input_csv_file_path="maptip.csv";
	std::string output_csv_file_path="maptip.csv";

	//�ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
	std::ifstream ifs_csv_file(input_csv_file_path);

	//��������csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
	std::ofstream ofs_csv_file(output_csv_file_path);

	//getline�֐���1�s���ǂݍ���(�ǂݍ��񂾓��e��str_buf�Ɋi�[)
	while (getline(ifs_csv_file,str_buf))
	{
		//�u,�v��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
		std::istringstream i_stream(str_buf);

		//�u,�v��؂育�ƂɃf�[�^��ǂݍ���
		while (getline(i_stream, str_conma_buf, ','))
		{
			//csv�t�@�C���ɏ�������
			ofs_csv_file << str_conma_buf << ',';
		}
		//���s����
		ofs_csv_file << std::endl;
	}
	// �N���[�Y�����͕s�v
	// [���R]ifstream�^�Eofstream�^�Ƃ��Ƀf�X�g���N�^�ɂăt�@�C���N���[�Y���Ă���邽��
}