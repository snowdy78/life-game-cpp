#include "../Engine.hpp"
#include <fstream>

namespace rn
{
	void JsonFile::create(const std::string &path, const std::string &fname)
	{
		/*
		* create a file.
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		using namespace std::string_literals;
		std::string com = "mkdir "s + path; // cmd command >>>mkdir <path>
		system(com.c_str()); // console file creating
		std::ofstream ofile(getFullPath(path, fname));
		if (!ofile.is_open())
		{
			std::cerr << "FileOpenErr: No such file or dirrectory\n";
			throw;
		}
		ofile.close();
	}

	std::string JsonFile::getFullPath(const std::string& path, const std::string& fname)
	{
		if (path.size() == 0)
			return fname + ".json";
		const char &lchar = path[path.size() - 1];
		return (lchar == '/' or lchar == '\\' ? path.substr(path.size() - 1) : path) + "\\" + fname + ".json"; // excepting way when file path end's "/" or "\"
	}

	JsonFile::JsonFile(const std::string &path, const std::string &fname, Json j)
		: path(path), file_name(fname), js(j)
	{
		load();
	}

	Json JsonFile::load(const std::string &path, const std::string &fname)
	{
		/*
		* loads a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		std::ifstream infile;
		const std::string full_path = getFullPath(path, fname);
		infile.open(full_path);
		if (!infile.is_open())
		{
			create(path, fname);
			infile.open(full_path);
		}
		std::string strjs; // json dumped string
		std::string line;
		while (!infile.eof())
		{
			infile >> line;
			strjs += line;
		}
		infile.close();
		if (strjs.empty())
			return {};

		return Json::parse(strjs);
	}

	Json JsonFile::load(const JsonFile &jsonf)
	{
		/*
		* loads a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		return load(jsonf.path, jsonf.file_name);
	}

	Json JsonFile::load()
	{
		/*
		* loads a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		return js = load(path, file_name);
	}

	std::string JsonFile::getFileName()
	{ return file_name; }

	std::string JsonFile::getPath()
	{ return path; }

	void JsonFile::save(std::string path, const std::string &fname, Json j)
	{
		/*
		* save a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		std::ofstream outf;
		const std::string full_path = getFullPath(path, fname);
		outf.open(full_path);
		if (!outf.is_open())
		{
			create(path, fname);
			outf.open(full_path);
		}
		outf << j.dump(4, ' ');
		outf.close();
	}


	void JsonFile::save() const
	{
		/*
		* save a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		save(path, file_name, js);
	}

	void JsonFile::save(const JsonFile &jsonf)
	{
		/*
		* save a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		save(jsonf.path, jsonf.file_name, jsonf.js);
	}
}