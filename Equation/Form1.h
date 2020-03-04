#pragma once

namespace Equation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;

	int x1;     // ��������������� ���������� (������� �� ����� � ������)
	double x3;  // �������� �������������� �����
	char ds;    // ������ ����������� �����������

	void Durak(System::Windows::Forms::TextBox^ txt, System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		// ���� ������� ������� �� ��������.
		if (!Char::IsDigit(e->KeyChar))
			// ������ �� ���� ����� ������ ����� ������.
			if (e->KeyChar != '-' || txt->Text->IndexOf('-') != -1)
			// ������ �� ���� ����� ������ ����������� �����������.
			if (e->KeyChar != ds || txt->Text->IndexOf(ds) != -1)
				// ���� ������� ������� �� �������� �������� BackSpace.
				if (e->KeyChar != (char)Keys::Back)
					e->Handled = true;          // ������ �����

		// ������ ����� ��������� ����� � ������ �����.
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0)  // ���� ������ ������� 0
			if (txt->Text->Length >= 1)        // ���� ������ �� ������
			if (txt->Text[0] == '0' && txt->SelectionStart < 2)
				e->Handled = true;             // ������ �����

		// ������ ����������� ����������� � ������ ����� �� "0,".
		if (e->KeyChar == ds) {    // ���� ������ ���������� �����������
			x1 = 0;
			if (txt->Text != "" && txt->Text[0] == '-') { x1 = 1; }
			if (txt->Text->IndexOf(ds) == -1 &&
				txt->SelectionStart == x1) {
			// ���� ���������� ����������� ��� ����, �� 0 ��������� �� �����
			txt->Text = txt->Text->Insert(x1, "0");  // ������� 0
			txt->SelectionStart = x1 + 1;  // ��������� ������ � �����
			}
		}

		// ������� ����� ����� ������ � ������ (���� ������ ������ �������)
		if (e->KeyChar == '-' && txt->Text->IndexOf('-') == -1)
			txt->SelectionStart = 0;         // ��������� ������ � ������

		// ������ �� ���� ����� ������ ������
		if (txt->Text->Length > 0)        // ���� ������ �� ������
		if (txt->Text[0] == '-' && txt->SelectionStart < 1) // ���� � ������ ������ �����
			e->Handled = true;

		// ������ ����� ������� ���� �� '0,', ���� ������ �� �������
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0) // ���� ������ 0
		// ���� ������ �� �������, ������ �������, � ��� �����������
		if (txt->Text->Length > 0 && txt->SelectionStart == 0 && txt->Text->IndexOf('-') == -1)
		{
			if (txt->Text[0] != ds)
			{
				if (txt->Text->IndexOf(ds) != -1) // ���� ��� ���� ���������� �����������
				{
					e->Handled = true; // ��������� ����
				}
				else // ���� ����������� ����������� ���
				{
					x1 = 0;
					e->KeyChar = ds; // ������ ������� �������� ������ �� ���� �����������
					txt->Text = txt->Text->Insert(x1, "0"); // ��������� ����� 0
					txt->SelectionStart = x1 + 1; // ��������� ������ �����
				}
			}
		}

		// ������ ����� �� '0,' ������� ����, ���� ������� �����
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0) // ���� ����� ����
		if (txt->Text->Length > 1 && txt->SelectionStart == 1
			&& Char::IsDigit(txt->Text[1]) && txt->Text->IndexOf('-') != -1)
		{
			if (txt->Text[0] != ds)
			{
				if (txt->Text->IndexOf(ds) != -1) // ���� ��� ���� ���������� �����������
				{
					e->Handled = true; // ��������� ����
				}
				else // ���� ����������� ����������� ���
				{
					x1 = 0;
					e->KeyChar = ds; // ������ ������� �������� ������ �� ���� �����������
					txt->Text = txt->Text->Insert(x1+1, "0"); // ��������� ����� 0
					txt->SelectionStart = x1 + 2; // ��������� ������ �����
				}
			}
		}

		// ������ ������� ���� �� �������� �����, ���� ������ ��� �����������
		if ((txt->Text->Length > 0 && txt->Text[0] == '0') // ���� ����� ������ 1, � ������� "0"
			&& Char::IsDigit(e->KeyChar)
			&& txt->SelectionStart == 1)
		{
			if (e->KeyChar != '0') // ���� ������ �� 0
			{
				txt->Text = txt->Text->Remove(0,1); // �������� ���� � ������
				txt->SelectionStart = 0; // ������� ������� � ������
			}
			else // ���� ������ 0
			{
				e->Handled = true; // ��������� ����
			}
		}

		// ������ ����� ���������� ����� ���� ����� ������
		if (txt->Text->Length > 1 && txt->Text[0] == '-'
			&& txt->Text[1] == '0' && Char::IsDigit(e->KeyChar)
			&& txt->SelectionStart == 2 && txt->Text[1] != ds) // ���� ����� ������ 2, � ������� "-0"
		{
			if (e->KeyChar != '0') // ���� ������ �� 0
			{
				txt->Text = txt->Text->Remove(1,1); // �������� ���� ����� ������
				txt->SelectionStart = 1; // ������ ������� �� 1 �������
			}
			else // ���� ������ 0
			{
				e->Handled = true; // ��������� ����
			}
		}

		// ������ �� ���� ���������� ����� ����� �������
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0) // ���� ����� 0
		// ���� ������ ���������, ���� ���� ����������� � ������ ����� � ������
		if (txt->Text->Length > 1 && txt->Text->IndexOf(ds) != -1 && txt->SelectionStart == txt->Text->Length)
		// ���� ����� �������� ����� �����, � ��� ����� �� 0
		if (Char::IsDigit(txt->Text[txt->Text->Length-1]) && txt->Text[txt->Text->Length-1] != '0')
		{
			e->Handled = true; // ��������� ����
		}


	}

	//������� ������������� ������ ��� �������� �� ������������ ��������� ��������
	bool IsTrueNumber(String^ txt)
	{
		bool boolStr = true; // ������ ���������� �� ���������
		if (txt->Length == 1 && txt[0] == '-') // ���� �������� ������������ �����
		{
			boolStr = false; // ������ ������
		}
		else if (txt[0] == '-' && txt[1] == ds) // ���� �������� '-,'
		{
			boolStr = false; // ������ ������
		}
		else if (txt[0] == ds || txt[txt->Length-1] == ds) // ���� �������� ����������� ������� ��� �����
		{
			boolStr = false; // ������ ������
		}
		return boolStr; // ������� ������ ��� ���������� ������
	}

	/// <summary>
	/// ������ ��� Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblKoeff;
	protected: 

	protected: 
	private: System::Windows::Forms::Label^  lblA;
	private: System::Windows::Forms::Label^  lblB;
	private: System::Windows::Forms::Label^  lblC;
	private: System::Windows::Forms::Label^  lblKorni;
	private: System::Windows::Forms::Label^  lblX1;
	private: System::Windows::Forms::Label^  lblX2;
	private: System::Windows::Forms::Label^  lblResult;
	private: System::Windows::Forms::TextBox^  txtA;
	private: System::Windows::Forms::TextBox^  txtX1;
	private: System::Windows::Forms::TextBox^  txtX2;
	private: System::Windows::Forms::TextBox^  txtB;
	private: System::Windows::Forms::TextBox^  txtC;
	private: System::Windows::Forms::Button^  btnReset;
	private: System::Windows::Forms::Button^  btnAction;

	private: System::Windows::Forms::Button^  button2;


	protected: 

	private:
		/// <summary>
		/// ��������� ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ������������ ����� ��� ��������� ������������ - �� ���������
		/// ���������� ������� ������ ��� ������ ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblKoeff = (gcnew System::Windows::Forms::Label());
			this->lblA = (gcnew System::Windows::Forms::Label());
			this->lblB = (gcnew System::Windows::Forms::Label());
			this->lblC = (gcnew System::Windows::Forms::Label());
			this->lblKorni = (gcnew System::Windows::Forms::Label());
			this->lblX1 = (gcnew System::Windows::Forms::Label());
			this->lblX2 = (gcnew System::Windows::Forms::Label());
			this->lblResult = (gcnew System::Windows::Forms::Label());
			this->txtA = (gcnew System::Windows::Forms::TextBox());
			this->txtX1 = (gcnew System::Windows::Forms::TextBox());
			this->txtX2 = (gcnew System::Windows::Forms::TextBox());
			this->txtB = (gcnew System::Windows::Forms::TextBox());
			this->txtC = (gcnew System::Windows::Forms::TextBox());
			this->btnReset = (gcnew System::Windows::Forms::Button());
			this->btnAction = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblKoeff
			// 
			this->lblKoeff->AutoSize = true;
			this->lblKoeff->BackColor = System::Drawing::Color::MidnightBlue;
			this->lblKoeff->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblKoeff->ForeColor = System::Drawing::SystemColors::Info;
			this->lblKoeff->Location = System::Drawing::Point(28, 9);
			this->lblKoeff->Name = L"lblKoeff";
			this->lblKoeff->Size = System::Drawing::Size(216, 58);
			this->lblKoeff->TabIndex = 0;
			this->lblKoeff->Text = L"������������\r\n���������";
			this->lblKoeff->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKoeff->Click += gcnew System::EventHandler(this, &Form1::lblKoeff_Click);
			// 
			// lblA
			// 
			this->lblA->AutoSize = true;
			this->lblA->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblA->ForeColor = System::Drawing::SystemColors::Info;
			this->lblA->Location = System::Drawing::Point(28, 77);
			this->lblA->Name = L"lblA";
			this->lblA->Size = System::Drawing::Size(64, 29);
			this->lblA->TabIndex = 1;
			this->lblA->Text = L"a =";
			this->lblA->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblB
			// 
			this->lblB->AutoSize = true;
			this->lblB->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblB->ForeColor = System::Drawing::SystemColors::Info;
			this->lblB->Location = System::Drawing::Point(28, 120);
			this->lblB->Name = L"lblB";
			this->lblB->Size = System::Drawing::Size(65, 29);
			this->lblB->TabIndex = 2;
			this->lblB->Text = L"b =";
			this->lblB->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblC
			// 
			this->lblC->AutoSize = true;
			this->lblC->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblC->ForeColor = System::Drawing::SystemColors::Info;
			this->lblC->Location = System::Drawing::Point(28, 165);
			this->lblC->Name = L"lblC";
			this->lblC->Size = System::Drawing::Size(64, 29);
			this->lblC->TabIndex = 3;
			this->lblC->Text = L"c =";
			this->lblC->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblC->Click += gcnew System::EventHandler(this, &Form1::lblC_Click);
			// 
			// lblKorni
			// 
			this->lblKorni->AutoSize = true;
			this->lblKorni->BackColor = System::Drawing::Color::MidnightBlue;
			this->lblKorni->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblKorni->ForeColor = System::Drawing::SystemColors::Info;
			this->lblKorni->Location = System::Drawing::Point(28, 234);
			this->lblKorni->Name = L"lblKorni";
			this->lblKorni->Size = System::Drawing::Size(236, 29);
			this->lblKorni->TabIndex = 4;
			this->lblKorni->Text = L"����� ���������";
			this->lblKorni->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKorni->Click += gcnew System::EventHandler(this, &Form1::lblKorni_Click);
			// 
			// lblX1
			// 
			this->lblX1->AutoSize = true;
			this->lblX1->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblX1->ForeColor = System::Drawing::SystemColors::Info;
			this->lblX1->Location = System::Drawing::Point(25, 293);
			this->lblX1->Name = L"lblX1";
			this->lblX1->Size = System::Drawing::Size(76, 29);
			this->lblX1->TabIndex = 5;
			this->lblX1->Text = L"x1 =";
			this->lblX1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblX1->Click += gcnew System::EventHandler(this, &Form1::lblX1_Click);
			// 
			// lblX2
			// 
			this->lblX2->AutoSize = true;
			this->lblX2->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblX2->ForeColor = System::Drawing::SystemColors::Info;
			this->lblX2->Location = System::Drawing::Point(25, 343);
			this->lblX2->Name = L"lblX2";
			this->lblX2->Size = System::Drawing::Size(79, 29);
			this->lblX2->TabIndex = 6;
			this->lblX2->Text = L"x2 =";
			this->lblX2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblX2->Click += gcnew System::EventHandler(this, &Form1::lblX2_Click);
			// 
			// lblResult
			// 
			this->lblResult->AutoSize = true;
			this->lblResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblResult->ForeColor = System::Drawing::Color::Green;
			this->lblResult->Location = System::Drawing::Point(254, 138);
			this->lblResult->Name = L"lblResult";
			this->lblResult->Size = System::Drawing::Size(0, 20);
			this->lblResult->TabIndex = 7;
			this->lblResult->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// txtA
			// 
			this->txtA->Location = System::Drawing::Point(98, 82);
			this->txtA->Name = L"txtA";
			this->txtA->Size = System::Drawing::Size(125, 22);
			this->txtA->TabIndex = 8;
			this->txtA->TextChanged += gcnew System::EventHandler(this, &Form1::txtA_TextChanged);
			this->txtA->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtA_KeyPress);
			// 
			// txtX1
			// 
			this->txtX1->Location = System::Drawing::Point(98, 298);
			this->txtX1->Name = L"txtX1";
			this->txtX1->ReadOnly = true;
			this->txtX1->Size = System::Drawing::Size(125, 22);
			this->txtX1->TabIndex = 9;
			this->txtX1->TextChanged += gcnew System::EventHandler(this, &Form1::txtX1_TextChanged);
			// 
			// txtX2
			// 
			this->txtX2->Location = System::Drawing::Point(98, 348);
			this->txtX2->Name = L"txtX2";
			this->txtX2->ReadOnly = true;
			this->txtX2->Size = System::Drawing::Size(125, 22);
			this->txtX2->TabIndex = 10;
			// 
			// txtB
			// 
			this->txtB->Location = System::Drawing::Point(98, 127);
			this->txtB->Name = L"txtB";
			this->txtB->Size = System::Drawing::Size(125, 22);
			this->txtB->TabIndex = 11;
			this->txtB->TextChanged += gcnew System::EventHandler(this, &Form1::txtB_TextChanged);
			this->txtB->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtB_KeyPress);
			// 
			// txtC
			// 
			this->txtC->Location = System::Drawing::Point(98, 172);
			this->txtC->Name = L"txtC";
			this->txtC->Size = System::Drawing::Size(125, 22);
			this->txtC->TabIndex = 12;
			this->txtC->TextChanged += gcnew System::EventHandler(this, &Form1::txtC_TextChanged);
			this->txtC->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtC_KeyPress);
			// 
			// btnReset
			// 
			this->btnReset->BackColor = System::Drawing::Color::MidnightBlue;
			this->btnReset->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->btnReset->ForeColor = System::Drawing::Color::White;
			this->btnReset->Location = System::Drawing::Point(303, 172);
			this->btnReset->Name = L"btnReset";
			this->btnReset->Size = System::Drawing::Size(208, 66);
			this->btnReset->TabIndex = 13;
			this->btnReset->Text = L"�����";
			this->btnReset->UseVisualStyleBackColor = false;
			this->btnReset->Click += gcnew System::EventHandler(this, &Form1::btnReset_Click);
			// 
			// btnAction
			// 
			this->btnAction->BackColor = System::Drawing::Color::MidnightBlue;
			this->btnAction->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->btnAction->ForeColor = System::Drawing::Color::White;
			this->btnAction->Location = System::Drawing::Point(303, 81);
			this->btnAction->Name = L"btnAction";
			this->btnAction->Size = System::Drawing::Size(208, 66);
			this->btnAction->TabIndex = 14;
			this->btnAction->Text = L"������";
			this->btnAction->UseVisualStyleBackColor = false;
			this->btnAction->Click += gcnew System::EventHandler(this, &Form1::btnAction_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::MidnightBlue;
			this->button2->Font = (gcnew System::Drawing::Font(L"Complex", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(303, 262);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(203, 66);
			this->button2->TabIndex = 15;
			this->button2->Text = L"�������";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Highlight;
			this->ClientSize = System::Drawing::Size(535, 405);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->btnAction);
			this->Controls->Add(this->btnReset);
			this->Controls->Add(this->txtC);
			this->Controls->Add(this->txtB);
			this->Controls->Add(this->txtX2);
			this->Controls->Add(this->txtX1);
			this->Controls->Add(this->txtA);
			this->Controls->Add(this->lblResult);
			this->Controls->Add(this->lblX2);
			this->Controls->Add(this->lblX1);
			this->Controls->Add(this->lblKorni);
			this->Controls->Add(this->lblC);
			this->Controls->Add(this->lblB);
			this->Controls->Add(this->lblA);
			this->Controls->Add(this->lblKoeff);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"������� ����������� ���������";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 // ����������� ����������� ����������� (����� ��� �������)
				 // �� ������������ ��������.
				 NumberFormatInfo^ nfi = NumberFormatInfo::CurrentInfo;
				 ds = (char)nfi->NumberDecimalSeparator[0];
			 }

	private: System::Void lblKorni_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

	// ��������� ������ "�������"
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close(); // ��������� ����
			 }

	// ��������� ������ "�����"
	private: System::Void btnReset_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->txtA->Text = L""; // �������� txtA
				 this->txtB->Text = L""; // �������� txtB
				 this->txtC->Text = L""; // �������� txtC
				 this->txtX1->Text = L""; // �������� txtX1
				 this->txtX2->Text = L""; // �������� txtX2
				 this->lblResult->Text = L""; // �������� txtResult
			 }

	// ��������� ������ "������"
	private: System::Void btnAction_Click(System::Object^  sender, System::EventArgs^  e) {
					// ���� ��������� ������
					try
					{
						if (txtA->Text->Length < 1 || txtB->Text->Length < 1 // ��������� �� ������ �� ������� ������
							|| txtC->Text->Length < 1)
						{
							throw 0; // ���������� ��� ������
						}

						if (IsTrueNumber(txtA->Text) == false ||
							IsTrueNumber(txtB->Text) == false || IsTrueNumber(txtC->Text) == false)
						{
							throw 'e';
						}

						this->lblResult->ForeColor = System::Drawing::Color::Green; // ������ LabelResult ������
						this->txtX1->Text = L"";
						this->txtX2->Text = L"";

						if (txtA->Text == "0" && txtB->Text == "0" && txtC->Text == "0")
						{
							this->lblResult->Text = L"������ ���������";
						}
						else if (txtA->Text == "0" && txtB->Text == "0" && txtC->Text != "0")
						{
							this->lblResult->Text = L"�������� ���������";
						}
						else if (txtA->Text == "0")
						{
							this->lblResult->Text = L"������� ������������ ������";
							this->lblResult->ForeColor = System::Drawing::Color::Red;
						}
						else
						{
							double a, b, c, Disc, x1, x2; // ��������� ���������� ��� ������� ������, ������������� � ������

							// ������������� ������� ������ ������������ ����������� �� � Double
							a = Convert::ToDouble(txtA->Text); // ������������ txtA
							b = Convert::ToDouble(txtB->Text); // ������������ txtB
							c = Convert::ToDouble(txtC->Text); // ������������ txtC

							Disc = Math::Pow(b,2) - 4*a*c; // ����� ������� ������������� � ����������� �������� � ���������� Disc

							if (Disc > 0) // ���� ������������ �������������
							{
								x1 = (-b + Math::Sqrt(Disc))/(2*a); // �� ������� ��������� x1
								x2 = (-b - Math::Sqrt(Disc))/(2*a); // �� ������� ��������� x2
								this->txtX1->Text = Convert::ToString(x1); // ����������� x1 � String
								this->txtX2->Text = Convert::ToString(x2); // ����������� x2 � String
								this->lblResult->Text = L"������������ > 0.\n��������� ����� ��� �����."; // ����� ��������� � �������������
							}
							else if (Disc == 0) // ���� ������������ �������
							{
								x1 = -b/2*a; // �� ������� ��������� x1
								x2 = -b/2*a; // �� ������� ��������� x2
								this->txtX1->Text = Convert::ToString(x1); // ������������ x1 � String
								this->txtX2->Text = Convert::ToString(x2); // ������������ x2 � String
								this->lblResult->Text = L"������������ = 0. ���������\n����� ��� ���������� �����."; // ����� ��������� � �������������
							}
							else // ���� ������������ �������������
							{
								this->lblResult->Text = L"������������ < 0.\n��������� �� ����� ������."; // ����� ��������� � ������������� 
							}
						}
					}
					catch(int a) // ��������� ������
					{
						this->lblResult->Text = L"���� ��� ���������\n��������� ����� ������!"; // ����� ��������� �� ������
						this->lblResult->ForeColor = System::Drawing::Color::Red; // ������ LabelResult �������
					}
					catch(char b)
					{
						this->lblResult->Text = "������� ������������ ������"; // ����� ��������� �� ������ 
						this->lblResult->ForeColor = System::Drawing::Color::Red; // ������ LabelResult �������
					}
				 
			 }

	private: System::Void txtA_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void txtB_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void txtC_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	// ����������� ����� � txtA ������ �������������� �����.
	// ���������� �������� � ���������� �������������� �����.
	private: System::Void txtA_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		Durak(txtA, sender, e); // ����� ������� ��� ������ �� ������
	}

	// ����������� ����� � txtB ������ �������������� �����.
	// ���������� �������� � ���������� �������������� �����.
	private: System::Void txtB_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		Durak(txtB, sender, e); // ����� ������� ��� ������ �� ������
	}

	// ����������� ����� � txtC ������ �������������� �����.
	// ���������� �������� � ���������� �������������� �����.
	private: System::Void txtC_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		Durak(txtC, sender, e); // ����� ������� ��� ������ �� ������
	}
private: System::Void lblKoeff_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void lblC_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void lblX2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void txtX1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void lblX1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

