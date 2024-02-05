#include "Information.h"

using namespace StoryViewer;

bool Information::use_inline = false;

Information::Information()
	: Object(), file_dir(), file_type(ANY)
{}

Information::Information(String _dir)
	: Object(), file_dir(_dir)
{
	//if (!_Valid(_dir))
	//{
	//	throw std::exception("Error : Invalid resource directory!");
	//	return;
	//}
	String _ext = _dir.substr(_dir.length() - 4);
	if (_ext == L".txt" || _ext == L".TXT")
		file_type = TEXT;
	else if (_ext == L".jpg" || _ext == L".JPG"
		|| _ext == L".png" || _ext == L".PNG")
		file_type = IMAGE;
	else if (_ext == L".mp3" || _ext == L".MP3"
		|| _ext == L".wav" || _ext == L".WAV")
		file_type = AUDIO;
	else if (_ext == L".mp4" || _ext == L".MP4")
		file_type = VIDEO;
	else
		file_type = ANY;
}

String Information::GetFileDir() const
{
	return file_dir;
}

void Information::SetFileDir(String _dir)
{
	//if (!_Valid(_dir))
	//{
	//	throw std::exception("Error : Invalid resource directory!");
	//	return;
	//}
	file_dir = _dir;
	String _ext = _dir.substr(_dir.length() - 4);
	if (_ext == L".txt" || _ext == L".TXT")
		file_type = TEXT;
	else if (_ext == L".jpg" || _ext == L".JPG"
		|| _ext == L".png" || _ext == L".PNG")
		file_type = IMAGE;
	else if (_ext == L".mp3" || _ext == L".MP3"
		|| _ext == L".wav" || _ext == L".WAV")
		file_type = AUDIO;
	else if (_ext == L".mp4" || _ext == L".MP4")
		file_type = VIDEO;
	else
		file_type = ANY;
	
}

bool Information::_Valid(String _dir)
{
	std::wifstream _tester(_dir.c_str());
	return _tester.good();
}

bool Information::Open()
{
	if (!_Valid(this->file_dir))
	{
		throw std::exception("Error : Invalid resource directory!");
		return false;
	}
	HINSTANCE _res = ShellExecute(nullptr, L"open", file_dir.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
	return ((intptr_t)_res > 32);
}

String Information::ToString(bool _detailed) const
{
	String _ret{};
	_ret += L"<文件";
	switch (file_type)
	{
	case TEXT:
		_ret += L"(文本)";
		break;
	case IMAGE:
		_ret += L"(图像)";
		break;
	case AUDIO:
		_ret += L"(音频)";
		break;
	case VIDEO:
		_ret += L"(视频)";
		break;
	default:
		break;
	}
	_ret += L">";
	if (!_detailed)
		return _ret;
	_ret += this->file_dir;
	return _ret;
}