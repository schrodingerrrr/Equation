#pragma once

namespace Equation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;

	int x1;     // Вспомогательная переменная (имеется ли минус в строке)
	double x3;  // Вводимое действительное число
	char ds;    // Символ десятичного разделителя

	void Durak(System::Windows::Forms::TextBox^ txt, System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		// Если нажатая клавиша не цифровая.
		if (!Char::IsDigit(e->KeyChar))
			// Запрет на ввод более одного знака минуса.
			if (e->KeyChar != '-' || txt->Text->IndexOf('-') != -1)
			// Запрет на ввод более одного десятичного разделителя.
			if (e->KeyChar != ds || txt->Text->IndexOf(ds) != -1)
				// Если нажатая клавиша не является клавишей BackSpace.
				if (e->KeyChar != (char)Keys::Back)
					e->Handled = true;          // Запрет ввода

		// Запрет ввода повторных нулей в начале числа.
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0)  // Если нажата клавиша 0
			if (txt->Text->Length >= 1)        // Если строка не пустая
			if (txt->Text[0] == '0' && txt->SelectionStart < 2)
				e->Handled = true;             // Запрет ввода

		// Замена десятичного разделителя в начале числа на "0,".
		if (e->KeyChar == ds) {    // Если введен десятичный разделитель
			x1 = 0;
			if (txt->Text != "" && txt->Text[0] == '-') { x1 = 1; }
			if (txt->Text->IndexOf(ds) == -1 &&
				txt->SelectionStart == x1) {
			// Если десятичный разделитель уже есть, то 0 вставлять не нужно
			txt->Text = txt->Text->Insert(x1, "0");  // Вставка 0
			txt->SelectionStart = x1 + 1;  // Текстовый курсор в конец
			}
		}

		// Перенос точки ввода минуса в начало (ввод минуса только спереди)
		if (e->KeyChar == '-' && txt->Text->IndexOf('-') == -1)
			txt->SelectionStart = 0;         // Текстовый курсор в начало

		// Запрет на ввод перед знаком минуса
		if (txt->Text->Length > 0)        // Если строка не пустая
		if (txt->Text[0] == '-' && txt->SelectionStart < 1) // Если в начале строки минус
			e->Handled = true;

		// Замена ввода первого нуля на '0,', если строка не нулевая
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0) // если нажата 0
		// если строка не нулевая, курсор впереди, и нет разделителя
		if (txt->Text->Length > 0 && txt->SelectionStart == 0 && txt->Text->IndexOf('-') == -1)
		{
			if (txt->Text[0] != ds)
			{
				if (txt->Text->IndexOf(ds) != -1) // если уже есть десятичный разделитель
				{
					e->Handled = true; // запрещаем ввод
				}
				else // если десятичного разделителя нет
				{
					x1 = 0;
					e->KeyChar = ds; // меняем текущий вводимый символ на знак разделителя
					txt->Text = txt->Text->Insert(x1, "0"); // добавляем слева 0
					txt->SelectionStart = x1 + 1; // переводим курсор вперёд
				}
			}
		}

		// Запрет ввода на '0,' первого нуля, если впереди минус
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0) // Если введён нуль
		if (txt->Text->Length > 1 && txt->SelectionStart == 1
			&& Char::IsDigit(txt->Text[1]) && txt->Text->IndexOf('-') != -1)
		{
			if (txt->Text[0] != ds)
			{
				if (txt->Text->IndexOf(ds) != -1) // если уже есть десятичный разделитель
				{
					e->Handled = true; // запрещаем ввод
				}
				else // если десятичного разделителя нет
				{
					x1 = 0;
					e->KeyChar = ds; // меняем текущий вводимый символ на знак разделителя
					txt->Text = txt->Text->Insert(x1+1, "0"); // добавляем слева 0
					txt->SelectionStart = x1 + 2; // переводим курсор вперёд
				}
			}
		}

		// Замена первого нуля на вводимую цифру, если дальше нет разделителя
		if ((txt->Text->Length > 0 && txt->Text[0] == '0') // если длина строки 1, и впереди "0"
			&& Char::IsDigit(e->KeyChar)
			&& txt->SelectionStart == 1)
		{
			if (e->KeyChar != '0') // если нажата не 0
			{
				txt->Text = txt->Text->Remove(0,1); // Удаление нуля в начале
				txt->SelectionStart = 0; // Перевод курсора в начало
			}
			else // если нажата 0
			{
				e->Handled = true; // запрещаем ввод
			}
		}

		// Запрет ввода повторного ввода нуля после минуса
		if (txt->Text->Length > 1 && txt->Text[0] == '-'
			&& txt->Text[1] == '0' && Char::IsDigit(e->KeyChar)
			&& txt->SelectionStart == 2 && txt->Text[1] != ds) // если длина строки 2, и впереди "-0"
		{
			if (e->KeyChar != '0') // если нажата не 0
			{
				txt->Text = txt->Text->Remove(1,1); // Удаление нуля после минуса
				txt->SelectionStart = 1; // Первод курсора на 1 позицию
			}
			else // если нажата 0
			{
				e->Handled = true; // запрещаем ввод
			}
		}

		// Запрет на ввод незначащих нулей после запятой
		if (e->KeyChar == (char)Keys::D0 ||
			e->KeyChar == (char)Keys::NumPad0) // если введён 0
		// если строка ненулевая, есть знак разделителя и курсор стоит в начале
		if (txt->Text->Length > 1 && txt->Text->IndexOf(ds) != -1 && txt->SelectionStart == txt->Text->Length)
		// если перед курсором стоит цифра, и эта цифра не 0
		if (Char::IsDigit(txt->Text[txt->Text->Length-1]) && txt->Text[txt->Text->Length-1] != '0')
		{
			e->Handled = true; // запрещаем ввод
		}


	}

	//Функция постобработки строки для проверки на корректность вводимого значения
	bool IsTrueNumber(String^ txt)
	{
		bool boolStr = true; // Строки корректные по умолчанию
		if (txt->Length == 1 && txt[0] == '-') // Если встречен единственный минус
		{
			boolStr = false; // Выдать ошибку
		}
		else if (txt[0] == '-' && txt[1] == ds) // Если встречен '-,'
		{
			boolStr = false; // Выдать ошибку
		}
		else if (txt[0] == ds || txt[txt->Length-1] == ds) // Если встречен разделитель вначале или конце
		{
			boolStr = false; // Выдать ошибку
		}
		return boolStr; // Вернуть ошибку или продолжить работу
	}

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
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
			this->lblKoeff->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblKoeff->Location = System::Drawing::Point(31, 19);
			this->lblKoeff->Name = L"lblKoeff";
			this->lblKoeff->Size = System::Drawing::Size(156, 40);
			this->lblKoeff->TabIndex = 0;
			this->lblKoeff->Text = L"Коэффициенты\r\nуравнения";
			this->lblKoeff->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblA
			// 
			this->lblA->AutoSize = true;
			this->lblA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblA->Location = System::Drawing::Point(21, 83);
			this->lblA->Name = L"lblA";
			this->lblA->Size = System::Drawing::Size(36, 20);
			this->lblA->TabIndex = 1;
			this->lblA->Text = L"a =";
			this->lblA->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblB
			// 
			this->lblB->AutoSize = true;
			this->lblB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblB->Location = System::Drawing::Point(21, 124);
			this->lblB->Name = L"lblB";
			this->lblB->Size = System::Drawing::Size(36, 20);
			this->lblB->TabIndex = 2;
			this->lblB->Text = L"b =";
			this->lblB->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblC
			// 
			this->lblC->AutoSize = true;
			this->lblC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblC->Location = System::Drawing::Point(21, 163);
			this->lblC->Name = L"lblC";
			this->lblC->Size = System::Drawing::Size(36, 20);
			this->lblC->TabIndex = 3;
			this->lblC->Text = L"c =";
			this->lblC->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblKorni
			// 
			this->lblKorni->AutoSize = true;
			this->lblKorni->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblKorni->Location = System::Drawing::Point(329, 29);
			this->lblKorni->Name = L"lblKorni";
			this->lblKorni->Size = System::Drawing::Size(168, 20);
			this->lblKorni->TabIndex = 4;
			this->lblKorni->Text = L"Корни уравнения";
			this->lblKorni->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKorni->Click += gcnew System::EventHandler(this, &Form1::lblKorni_Click);
			// 
			// lblX1
			// 
			this->lblX1->AutoSize = true;
			this->lblX1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblX1->Location = System::Drawing::Point(221, 83);
			this->lblX1->Name = L"lblX1";
			this->lblX1->Size = System::Drawing::Size(45, 20);
			this->lblX1->TabIndex = 5;
			this->lblX1->Text = L"x1 =";
			this->lblX1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblX2
			// 
			this->lblX2->AutoSize = true;
			this->lblX2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblX2->Location = System::Drawing::Point(402, 83);
			this->lblX2->Name = L"lblX2";
			this->lblX2->Size = System::Drawing::Size(45, 20);
			this->lblX2->TabIndex = 6;
			this->lblX2->Text = L"x2 =";
			this->lblX2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
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
			this->txtA->Location = System::Drawing::Point(63, 83);
			this->txtA->Name = L"txtA";
			this->txtA->Size = System::Drawing::Size(124, 22);
			this->txtA->TabIndex = 8;
			this->txtA->TextChanged += gcnew System::EventHandler(this, &Form1::txtA_TextChanged);
			this->txtA->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtA_KeyPress);
			// 
			// txtX1
			// 
			this->txtX1->Location = System::Drawing::Point(272, 83);
			this->txtX1->Name = L"txtX1";
			this->txtX1->ReadOnly = true;
			this->txtX1->Size = System::Drawing::Size(124, 22);
			this->txtX1->TabIndex = 9;
			// 
			// txtX2
			// 
			this->txtX2->Location = System::Drawing::Point(452, 83);
			this->txtX2->Name = L"txtX2";
			this->txtX2->ReadOnly = true;
			this->txtX2->Size = System::Drawing::Size(124, 22);
			this->txtX2->TabIndex = 10;
			// 
			// txtB
			// 
			this->txtB->Location = System::Drawing::Point(63, 124);
			this->txtB->Name = L"txtB";
			this->txtB->Size = System::Drawing::Size(124, 22);
			this->txtB->TabIndex = 11;
			this->txtB->TextChanged += gcnew System::EventHandler(this, &Form1::txtB_TextChanged);
			this->txtB->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtB_KeyPress);
			// 
			// txtC
			// 
			this->txtC->Location = System::Drawing::Point(63, 163);
			this->txtC->Name = L"txtC";
			this->txtC->Size = System::Drawing::Size(124, 22);
			this->txtC->TabIndex = 12;
			this->txtC->TextChanged += gcnew System::EventHandler(this, &Form1::txtC_TextChanged);
			this->txtC->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtC_KeyPress);
			// 
			// btnReset
			// 
			this->btnReset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->btnReset->Location = System::Drawing::Point(63, 214);
			this->btnReset->Name = L"btnReset";
			this->btnReset->Size = System::Drawing::Size(124, 30);
			this->btnReset->TabIndex = 13;
			this->btnReset->Text = L"Сброс";
			this->btnReset->UseVisualStyleBackColor = true;
			this->btnReset->Click += gcnew System::EventHandler(this, &Form1::btnReset_Click);
			// 
			// btnAction
			// 
			this->btnAction->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->btnAction->Location = System::Drawing::Point(235, 214);
			this->btnAction->Name = L"btnAction";
			this->btnAction->Size = System::Drawing::Size(124, 30);
			this->btnAction->TabIndex = 14;
			this->btnAction->Text = L"Решить";
			this->btnAction->UseVisualStyleBackColor = true;
			this->btnAction->Click += gcnew System::EventHandler(this, &Form1::btnAction_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(406, 214);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(124, 30);
			this->button2->TabIndex = 15;
			this->button2->Text = L"Закрыть";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(594, 265);
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
			this->Text = L"Решение квадратного уравнения";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 // Определение десятичного разделителя (точки или запятой)
				 // из региональных настроек.
				 NumberFormatInfo^ nfi = NumberFormatInfo::CurrentInfo;
				 ds = (char)nfi->NumberDecimalSeparator[0];
			 }

	private: System::Void lblKorni_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

	// Обработка кнопки "Закрыть"
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close(); // Закрываем окно
			 }

	// Обработка кнопки "Сброс"
	private: System::Void btnReset_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->txtA->Text = L""; // Обнуляем txtA
				 this->txtB->Text = L""; // Обнуляем txtB
				 this->txtC->Text = L""; // Обнуляем txtC
				 this->txtX1->Text = L""; // Обнуляем txtX1
				 this->txtX2->Text = L""; // Обнуляем txtX2
				 this->lblResult->Text = L""; // Обнуляем txtResult
			 }

	// Обработка кнопки "Решить"
	private: System::Void btnAction_Click(System::Object^  sender, System::EventArgs^  e) {
					// Блок обработки ошибки
					try
					{
						if (txtA->Text->Length < 1 || txtB->Text->Length < 1 // Проверяем не пустые ли входные данные
							|| txtC->Text->Length < 1)
						{
							throw 0; // возвращаем код ошибки
						}

						if (IsTrueNumber(txtA->Text) == false ||
							IsTrueNumber(txtB->Text) == false || IsTrueNumber(txtC->Text) == false)
						{
							throw 'e';
						}

						this->lblResult->ForeColor = System::Drawing::Color::Green; // Делаем LabelResult зелёным
						this->txtX1->Text = L"";
						this->txtX2->Text = L"";

						if (txtA->Text == "0" && txtB->Text == "0" && txtC->Text == "0")
						{
							this->lblResult->Text = L"Верное равенство";
						}
						else if (txtA->Text == "0" && txtB->Text == "0" && txtC->Text != "0")
						{
							this->lblResult->Text = L"Неверное равенство";
						}
						else if (txtA->Text == "0")
						{
							this->lblResult->Text = L"Введены неккоректные данные";
							this->lblResult->ForeColor = System::Drawing::Color::Red;
						}
						else
						{
							double a, b, c, Disc, x1, x2; // Объявляем переменные для входных данных, дискриминанта и корней

							// инициализация входных данных посредоством конвертации их в Double
							a = Convert::ToDouble(txtA->Text); // конвертируем txtA
							b = Convert::ToDouble(txtB->Text); // конвертируем txtB
							c = Convert::ToDouble(txtC->Text); // конвертируем txtC

							Disc = Math::Pow(b,2) - 4*a*c; // Задаём формулу дискриминанта и присваиваем значение в переменную Disc

							if (Disc > 0) // Если дискриминант положительный
							{
								x1 = (-b + Math::Sqrt(Disc))/(2*a); // По формуле вычисляем x1
								x2 = (-b - Math::Sqrt(Disc))/(2*a); // По формуле вычисляем x2
								this->txtX1->Text = Convert::ToString(x1); // Конвертиаця x1 в String
								this->txtX2->Text = Convert::ToString(x2); // Конвертиаця x2 в String
								this->lblResult->Text = L"Дискриминант > 0.\nУравнение имеет два корня."; // Вывод сообщения о дискриминанте
							}
							else if (Disc == 0) // Если дискриминант нулевой
							{
								x1 = -b/2*a; // По формуле вычисляем x1
								x2 = -b/2*a; // По формуле вычисляем x2
								this->txtX1->Text = Convert::ToString(x1); // Конвертиация x1 в String
								this->txtX2->Text = Convert::ToString(x2); // Конвертиация x2 в String
								this->lblResult->Text = L"Дискриминант = 0. Уравнение\nимеет два одинаковых корня."; // Вывод сообщения о дискриминанте
							}
							else // Если дискриминант отрицательный
							{
								this->lblResult->Text = L"Дискриминант < 0.\nУравнение не имеет корней."; // Вывод сообщения о дискриминанте 
							}
						}
					}
					catch(int a) // обработка ошибки
					{
						this->lblResult->Text = L"Одно или несколько\nтекстовых полей пустые!"; // Вывод сообщения об ошибке
						this->lblResult->ForeColor = System::Drawing::Color::Red; // Делаем LabelResult красным
					}
					catch(char b)
					{
						this->lblResult->Text = "Введены некорректные данные"; // Вывод сообщения об ошибке 
						this->lblResult->ForeColor = System::Drawing::Color::Red; // Делаем LabelResult красным
					}
				 
			 }

	private: System::Void txtA_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void txtB_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void txtC_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	// Организация ввода в txtA только действительных чисел.
	// Фильтрация вводимых с клавиатуры действительных чисел.
	private: System::Void txtA_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		Durak(txtA, sender, e); // Вызов функции для защиты от дурака
	}

	// Организация ввода в txtB только действительных чисел.
	// Фильтрация вводимых с клавиатуры действительных чисел.
	private: System::Void txtB_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		Durak(txtB, sender, e); // Вызов функции для защиты от дурака
	}

	// Организация ввода в txtC только действительных чисел.
	// Фильтрация вводимых с клавиатуры действительных чисел.
	private: System::Void txtC_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		Durak(txtC, sender, e); // Вызов функции для защиты от дурака
	}
};
}

