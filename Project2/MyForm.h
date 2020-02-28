#pragma once
#include <cliext/vector>

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SQLite;
	using namespace System::Text;
	using namespace cliext;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}


		SQLiteConnection^ db;
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}

			db->Close();
		}

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 80);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(220, 286);
			this->textBox1->TabIndex = 1;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"test.db";
			this->openFileDialog1->Filter = L"Файлы БД (*.db)|*.db";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(35, 33);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Перегляд";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::Button1_Click_1);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(256, 33);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(123, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Відкрити базу даних";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::Button2_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(256, 80);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(603, 286);
			this->dataGridView1->TabIndex = 4;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(400, 33);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(123, 23);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Додати запис";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::Button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(541, 33);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(123, 23);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Видалити запис";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::Button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(882, 424);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			textBox1->Clear();
			String^ fileName = openFileDialog1->FileName;

			SQLiteConnection^ db = gcnew SQLiteConnection();
			try
			{
				db->ConnectionString = "Data Source=\"" + fileName + "\"";
				db->Open();

				// Display Table
				try
				{
					SQLiteCommand^ cmdSelect = db->CreateCommand();
					cmdSelect->CommandText = "SELECT * FROM KYRSU;";
					SQLiteDataReader^ reader = cmdSelect->ExecuteReader();
					StringBuilder^ sb = gcnew StringBuilder();
					for (int colCtr = 0; colCtr < reader->FieldCount; ++colCtr)
					{
						// Add Seperator (If After First Column)
						if (colCtr > 0) sb->Append("|");

						// Add Column Name
						sb->Append(reader->GetName(colCtr));
					}
					sb->AppendLine();
					sb->Append("~~~~~~~~~~~~");
					sb->AppendLine();
					while (reader->Read())
					{
						for (int colCtr = 0; colCtr < reader->FieldCount; ++colCtr)
						{
							// Add Seperator (If After First Column)
							if (colCtr > 0) sb->Append("|");

							// Add Column Text
							sb->Append(reader->GetValue(colCtr)->ToString());
						}
						sb->AppendLine();
					}

					textBox1->Text = sb->ToString();
				}
				catch (Exception^ e)
				{
					MessageBox::Show("Error Executing SQL: " + e->ToString(), "Exception While Displaying MyTable ...");
				}

				db->Close();
			}
			finally
			{
				delete (IDisposable^)db;
			}
		}
	}
			 private: DataTable^ fillDataTable() {
				 DataTable^ table;
				 try
				 {
					 SQLiteCommand^ cmdSelect = db->CreateCommand();
					 //Обратите внимание, что SQL запрос оформляем как обычную строчку
					 cmdSelect->CommandText = "SELECT * FROM KYRSU;";
					 SQLiteDataReader^ reader = cmdSelect->ExecuteReader();

					 //Переменные
					 DataColumn^ column; //Столбец таблицы
					 DataRow^ row; //Строка таблицы

					 //Создаем таблицу данных
					 table = gcnew DataTable();

					 //Вектор названий столбцов
					 vector<String^>^ nameColumns = gcnew vector<String^>();

					 //Заполним данные о столбцах
					 for (int i = 0; i < reader->FieldCount; i++) {
						 nameColumns->push_back(reader->GetName(i));
						 column = gcnew DataColumn(nameColumns->at(i), String::typeid);
						 table->Columns->Add(column);
					 }

					 //Пробегаем по каждой записи
					 while (reader->Read()) {
						 //Заполняем строчку таблицы
						 row = table->NewRow();
						 //В каждой записи пробегаем по всем столбцам
						 for (int i = 0; i < reader->FieldCount; i++) {
							 //Добавляем значение столбца в row
							 row[nameColumns->at(i)] = reader->GetValue(i)->ToString();
							 reader->GetValue(i)->ToString();
						 }
						 table->Rows->Add(row);
					 }
				 }
				 catch (Exception^ e)
				 {
					 MessageBox::Show("Error Executing SQL: " + e->ToString(), "Exception While Displaying MyTable ...");
				 }
				 return table;
			 }
	private: System::Void Button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ fileName = openFileDialog1->FileName;

			db = gcnew SQLiteConnection();
			try
			{
				db->ConnectionString = "Data Source=\"" + fileName + "\"";
				db->Open();

				DataTable^ table = fillDataTable();

				dataGridView1->DataSource = table;
			}
			catch (Exception^ e)
			{
				MessageBox::Show("Error Working SQL: " + e->ToString(), "Exception ...");
			}
		}

	}


private: System::Void Button3_Click(System::Object^ sender, System::EventArgs^ e) {
	try
	{
		SQLiteCommand^ cmdInsertValue = db->CreateCommand();
		cmdInsertValue->CommandText = "INSERT INTO KYRSU (name kyrs, vukladach, student, group, result) VALUES('Фізика', 'Кнігініцький О.В.', 'Вірт М.Я.', 'КНК-31', 'зарах');";
		cmdInsertValue->ExecuteNonQuery();

		DataTable^ table = fillDataTable();

		dataGridView1->DataSource = table;
	}
	catch (Exception^ e)
	{
		MessageBox::Show("Error Executing SQL: " + e->ToString(), "Exception ...");
	}
}
private: System::Void Button4_Click(System::Object^ sender, System::EventArgs^ e) {
	//Номер выделенной строки
	int index = dataGridView1->CurrentCell->RowIndex;
	//Определим _id в выделенной строке
	String^ _id = dataGridView1->Rows[index]->Cells["_id"]->Value->ToString();

	try
	{
		SQLiteCommand^ cmdInsertValue = db->CreateCommand();
		cmdInsertValue->CommandText = "DELETE FROM KYRSU WHERE _id = " + _id + ";";
		cmdInsertValue->ExecuteNonQuery();

		DataTable^ table = fillDataTable();

		dataGridView1->DataSource = table;
	}
	catch (Exception^ e)
	{
		MessageBox::Show("Error Executing SQL: " + e->ToString(), "Exception ...");
	}
}
};

}
