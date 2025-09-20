#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <algorithm> // For std::min

// Platform-specific includes for directory listing
#ifdef _WIN32
#include <windows.h>
// Removed <codecvt> and <locale> as they are unreliable in some compilers
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

// HTML 模板
const std::string HTML_TEMPLATE = R"HTML_TEMPLATE(<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><!--TITLE_PLACEHOLDER--> - 我的个人博客</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Noto+Sans+SC:wght@400;700&display=swap" rel="stylesheet">
    <link href="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/themes/prism-tomorrow.min.css" rel="stylesheet" />
    
    <script>
        MathJax = {
            tex: {
                inlineMath: [['$', '$'], ['\\(', '\\)']],
                displayMath: [['$$', '$$'], ['\\[', '\\]']]
            },
            svg: {
                fontCache: 'global'
            }
        };
    </script>
    <script src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js" id="MathJax-script" async></script>
    
    <style>
        body { background-size: cover; background-position: center; background-attachment: fixed; font-family: 'Noto Sans SC', sans-serif; transition: background-image 1s ease-in-out; }
        .card { box-shadow: 0 4px 6px -1px rgb(0 0 0 / 0.1), 0 2px 4px -2px rgb(0 0 0 / 0.1); border: 1px solid rgba(0,0,0,0.05); }
        html { scroll-behavior: smooth; }
        pre[class*="language-"] { padding: 1rem; margin: 1.5rem 0; border-radius: 0.5rem; }
        :not(pre) > code {
            background-color: #f3f4f6;
            color: #be123c;
            padding: 0.125rem 0.375rem;
            border-radius: 0.25rem;
            font-size: 0.9em;
        }
    </style>
</head>
<body class="bg-gray-100 text-gray-800">
    <div class="container mx-auto p-4 lg:p-8">
        <header class="text-center mb-8">
            <h1 class="text-5xl font-bold text-gray-900 tracking-wider">Alexxtl的博客</h1>
            <p class="text-gray-600 mt-2">记录、分享、成长</p>
        </header>
        <div class="flex flex-col lg:flex-row gap-8">
            <aside class="w-full lg:w-1/4 flex-shrink-0">
                <div class="space-y-8">
                    <div class="bg-white/70 backdrop-blur-sm rounded-xl p-6 text-center card">
                        <img src="images/avatar.png" alt="博主头像" class="w-32 h-32 rounded-full mx-auto mb-4 border-4 border-white shadow-lg">
                        <h2 class="text-2xl font-bold">Alexxtl</h2>
                        <p class="text-gray-600 mt-2">一个热爱技术与生活的开发者。</p>
                        <div class="flex justify-center flex-wrap gap-x-4 gap-y-2 mt-4">
                            <a href="https://github.com/Alexxtl" target="_blank" class="text-gray-500 hover:text-indigo-600 transition-colors">GitHub</a>
                            <a href="https://www.luogu.com.cn/user/598187" target="_blank" class="text-gray-500 hover:text-indigo-600 transition-colors">Luogu</a>
                            <a href="https://blog.csdn.net/Alexxtl" target="_blank" class="text-gray-500 hover:text-indigo-600 transition-colors">CSDN</a>
                            <a href="https://codeforces.com/profile/Alex_xtl" target="_blank" class="text-gray-500 hover:text-indigo-600 transition-colors">Codeforces</a>
                            <a href="https://atcoder.jp/users/xiaotianlin" target="_blank" class="text-gray-500 hover:text-indigo-600 transition-colors">AtCoder</a>
                        </div>
                    </div>
                    <div class="bg-white/70 backdrop-blur-sm rounded-xl p-6 card">
                        <h3 class="text-xl font-bold mb-4 border-b pb-2">文章标签</h3>
                        <div class="flex flex-wrap gap-2">
                           <!--TAGS_PLACEHOLDER-->
                        </div>
                    </div>
                    <div class="bg-white/70 backdrop-blur-sm rounded-xl p-6 card">
                        <h3 class="text-xl font-bold mb-4 border-b pb-2">友情链接</h3>
                        <ul class="space-y-3 text-gray-700">
                            <li><a href="https://blog.csdn.net/BabyFalse?type=blog" class="hover:text-indigo-600 transition-colors" target="_blank">xwj</a></li>
                            <li><a href="https://www.cnblogs.com/MrSWdAxiv" class="hover:text-indigo-600 transition-colors" target="_blank">fzy</a></li>
                        </ul>
                    </div>
                </div>
            </aside>
            <main class="w-full lg:flex-grow bg-white/70 backdrop-blur-sm rounded-xl p-8 lg:p-12 card">
                <a href="https://alexxtl.github.io/blog/" class="text-indigo-600 hover:underline mb-6 inline-block">&larr; 返回首页</a>
                <h1 class="text-4xl font-bold mb-4 text-gray-900"><!--TITLE_PLACEHOLDER--></h1>
                <div class="text-gray-500 mb-8 border-b pb-4">
                    <span>发布于：<!--DATE_PLACEHOLDER--></span> | 
                    <span>作者：Alexxtl</span> | 
                    <!--CATEGORY_PLACEHOLDER-->
                </div>
                <article class="prose prose-lg max-w-none text-gray-800">
<!--CONTENT_PLACEHOLDER-->
                </article>
            </main>
        </div>
    </div>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/components/prism-core.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/plugins/autoloader/prism-autoloader.min.js"></script>
    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const reliableApi = 'https://api.waifu.pics/sfw/waifu';
            fetch(reliableApi).then(response => response.json()).then(data => {
                const img = new Image();
                img.src = data.url;
                img.onload = () => { document.body.style.backgroundImage = `url('${data.url}')`; };
            }).catch(() => { document.body.style.backgroundColor = '#f3f4f6'; });
        });
    </script>
</body>
</html>)HTML_TEMPLATE";

// --- Helper Functions ---
void replace_all(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::string escape_html(const std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    return buffer;
}

std::tm localtime_safe(const std::time_t& t) {
    std::tm tm_snapshot;
#if defined(_MSC_VER)
    localtime_s(&tm_snapshot, &t);
#else
    localtime_r(&t, &tm_snapshot);
#endif
    return tm_snapshot;
}

// --- Markdown Parsing Engine ---
std::string parse_inline_markdown(std::string line);

size_t find_next_token(const std::string& text, size_t start_pos) {
    size_t p1 = text.find('`', start_pos);
    size_t p2 = text.find("**", start_pos);
    size_t p3 = text.find("~~", start_pos);
    size_t p4 = text.find('[', start_pos);
    size_t p5 = text.find('$', start_pos);
    size_t next_pos = std::string::npos;
    if (p1 != std::string::npos) next_pos = (next_pos == std::string::npos) ? p1 : std::min(next_pos, p1);
    if (p2 != std::string::npos) next_pos = (next_pos == std::string::npos) ? p2 : std::min(next_pos, p2);
    if (p3 != std::string::npos) next_pos = (next_pos == std::string::npos) ? p3 : std::min(next_pos, p3);
    if (p4 != std::string::npos) next_pos = (next_pos == std::string::npos) ? p4 : std::min(next_pos, p4);
    if (p5 != std::string::npos) next_pos = (next_pos == std::string::npos) ? p5 : std::min(next_pos, p5);
    return next_pos;
}

std::string parse_inline_markdown(std::string line) {
    std::string result;
    size_t last_pos = 0;
    while (last_pos < line.length()) {
        size_t next_pos = find_next_token(line, last_pos);
        if (next_pos == std::string::npos) { result += line.substr(last_pos); break; }
        result += line.substr(last_pos, next_pos - last_pos);
        last_pos = next_pos;

        if (line[last_pos] == '$') {
            const std::string delim = (line.substr(last_pos, 2) == "$$") ? "$$" : "$";
            size_t end_pos = line.find(delim, last_pos + delim.length());
            if (end_pos != std::string::npos) {
                result += line.substr(last_pos, end_pos - last_pos + delim.length());
                last_pos = end_pos + delim.length();
            } else { result += '$'; last_pos++; }
        } else if (line[last_pos] == '`') {
            size_t end_pos = line.find('`', last_pos + 1);
            if (end_pos != std::string::npos) {
                result += "<code>" + escape_html(line.substr(last_pos + 1, end_pos - last_pos - 1)) + "</code>";
                last_pos = end_pos + 1;
            } else { result += '`'; last_pos++; }
        } else if (line.substr(last_pos, 2) == "**") {
            size_t end_pos = line.find("**", last_pos + 2);
            if (end_pos != std::string::npos) {
                result += "<strong>" + parse_inline_markdown(line.substr(last_pos + 2, end_pos - last_pos - 2)) + "</strong>";
                last_pos = end_pos + 2;
            } else { result += "**"; last_pos += 2; }
        } else if (line.substr(last_pos, 2) == "~~") {
            size_t end_pos = line.find("~~", last_pos + 2);
            if (end_pos != std::string::npos) {
                result += "<del>" + parse_inline_markdown(line.substr(last_pos + 2, end_pos - last_pos - 2)) + "</del>";
                last_pos = end_pos + 2;
            } else { result += "~~"; last_pos += 2; }
        } else if (line[last_pos] == '[') {
            size_t link_end = line.find("]", last_pos);
            size_t url_start = line.find("(", link_end);
            size_t url_end = line.find(")", url_start);
            if (link_end != std::string::npos && url_start == link_end + 1 && url_end != std::string::npos) {
                std::string text = line.substr(last_pos + 1, link_end - last_pos - 1);
                std::string url = line.substr(url_start + 1, url_end - url_start - 1);
                result += "<a href=\"" + url + "\" class=\"text-indigo-600 hover:underline\" target=\"_blank\">" + parse_inline_markdown(text) + "</a>";
                last_pos = url_end + 1;
            } else { result += '['; last_pos++; }
        }
    }
    return result;
}

std::string parse_content_to_html(std::istream& input) {
    std::stringstream output;
    std::string line;
    enum State { NORMAL, IN_CODE_BLOCK, IN_MATH_BLOCK };
    State current_state = NORMAL;
    std::stringstream block_buffer;
    std::string code_lang = "";
    bool in_list = false;

    auto flush_list_if_needed = [&]() {
        if (in_list) { output << "</ul>\n"; in_list = false; }
    };

    while (std::getline(input, line)) {
        switch (current_state) {
            case NORMAL:
                if (line.rfind("```", 0) == 0) {
                    flush_list_if_needed(); current_state = IN_CODE_BLOCK; code_lang = line.substr(3);
                } else if (line.rfind("$$", 0) == 0) {
                    flush_list_if_needed(); block_buffer << line << "\n";
                    if (line.find("$$", 2) == std::string::npos) { current_state = IN_MATH_BLOCK; } 
                    else { output << "<p>" << block_buffer.str() << "</p>\n"; block_buffer.str(""); }
                } else if (line.length() >= 3 && (line.find_first_not_of('-') == std::string::npos || line.find_first_not_of('*') == std::string::npos)) {
                    flush_list_if_needed(); output << "<hr class=\"my-8 border-gray-300\">\n";
                } 
                // 修正：从H6到H1检查，确保正确匹配
                else if (line.rfind("###### ", 0) == 0) {
                    flush_list_if_needed(); output << "<h6 class=\"text-sm font-bold mt-4 mb-2 text-gray-700\">" << parse_inline_markdown(line.substr(7)) << "</h6>\n";
                } else if (line.rfind("##### ", 0) == 0) {
                    flush_list_if_needed(); output << "<h5 class=\"text-base font-bold mt-4 mb-2\">" << parse_inline_markdown(line.substr(6)) << "</h5>\n";
                } else if (line.rfind("#### ", 0) == 0) {
                    flush_list_if_needed(); output << "<h4 class=\"text-lg font-bold mt-5 mb-2\">" << parse_inline_markdown(line.substr(5)) << "</h4>\n";
                } else if (line.rfind("### ", 0) == 0) {
                    flush_list_if_needed(); output << "<h3 class=\"text-xl font-bold mt-6 mb-3\">" << parse_inline_markdown(line.substr(4)) << "</h3>\n";
                } else if (line.rfind("## ", 0) == 0) {
                    flush_list_if_needed(); output << "<h2 class=\"text-2xl font-bold mt-8 mb-4\">" << parse_inline_markdown(line.substr(3)) << "</h2>\n";
                } else if (line.rfind("# ", 0) == 0) {
                    flush_list_if_needed(); output << "<h1 class=\"text-3xl font-bold mt-10 mb-5\">" << parse_inline_markdown(line.substr(2)) << "</h1>\n";
                } 
                else if (line.rfind("- ", 0) == 0) {
                    if (!in_list) { output << "<ul class=\"list-disc pl-5 my-4\">\n"; in_list = true; }
                    output << "<li>" << parse_inline_markdown(line.substr(2)) << "</li>\n";
                } else if (line.empty()) {
                    flush_list_if_needed();
                } else {
                    flush_list_if_needed(); output << "<p>" << parse_inline_markdown(line) << "</p>\n";
                }
                break;
            case IN_CODE_BLOCK:
                if (line.rfind("```", 0) == 0) {
                    output << "<pre><code class=\"language-" << (code_lang.empty() ? "plain" : code_lang) << "\">" 
                           << escape_html(block_buffer.str()) << "</code></pre>\n";
                    block_buffer.str(""); current_state = NORMAL;
                } else { block_buffer << line << "\n"; }
                break;
            case IN_MATH_BLOCK:
                block_buffer << line << "\n";
                if (line.find("$$") != std::string::npos) {
                    output << "<p>" << block_buffer.str() << "</p>\n";
                    block_buffer.str(""); current_state = NORMAL;
                }
                break;
        }
    }
    flush_list_if_needed();
    return output.str();
}

// --- File System & Batch Processing ---

std::vector<std::string> list_txt_files(const std::string& directory) {
    std::vector<std::string> files;
#ifdef _WIN32
    auto to_wstring = [](const std::string& str) -> std::wstring {
        if (str.empty()) return std::wstring();
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    };
    auto to_string = [](const std::wstring& wstr) -> std::string {
        if (wstr.empty()) return std::string();
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
        std::string strTo(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
        return strTo;
    };

    std::string search_path = directory + "\\*.txt";
    WIN32_FIND_DATAW fd;
    std::wstring w_search_path = to_wstring(search_path);
    HANDLE hFind = FindFirstFileW(w_search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                files.push_back(to_string(fd.cFileName));
            }
        } while (FindNextFileW(hFind, &fd));
        FindClose(hFind);
    }
#else
    DIR* dir = opendir(directory.c_str());
    if (dir == NULL) { return files; }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string filename = entry->d_name;
        if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".txt") {
            files.push_back(filename);
        }
    }
    closedir(dir);
#endif
    return files;
}

std::string generate_preview_html(const std::string& title, const std::string& summary, const std::string& date_str, const std::string& category, const std::string& html_filename) {
    std::stringstream ss;
    ss << "<!-- Article Preview for: " << escape_html(title) << " -->\n";
    ss << "<article class=\"bg-white/70 backdrop-blur-sm rounded-xl p-8 lg:p-10 card transition-shadow hover:shadow-xl article-item\">\n";
    ss << "    <h2 class=\"text-3xl font-bold mb-3\">\n";
    ss << "        <a href=\"article/" << html_filename << "\" class=\"text-gray-900 hover:text-indigo-600\">" << escape_html(title) << "</a>\n";
    ss << "    </h2>\n";
    ss << "    <div class=\"text-gray-500 text-sm mb-4\">\n";
    ss << "        <span>" << date_str << "</span> | <span>分类：<a href=\"#\" class=\"text-pink-600 hover:underline\">" << escape_html(category) << "</a></span>\n";
    ss << "    </div>\n";
    ss << "    <p class=\"text-gray-700 leading-relaxed mb-6\">\n";
    ss << "        " << escape_html(summary) << "...\n";
    ss << "    </p>\n";
    ss << "    <a href=\"article/" << html_filename << "\" class=\"inline-block bg-indigo-600 text-white font-bold py-2 px-5 rounded-lg hover:bg-indigo-700 transition-colors\">阅读全文 &rarr;</a>\n";
    ss << "</article>\n\n";
    return ss.str();
}

std::string create_summary(const std::string& full_content) {
    std::string summary;
    std::istringstream content_stream(full_content);
    std::string line;
    while (summary.length() < 200 && std::getline(content_stream, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");
        if (std::string::npos == first) continue;
        line = line.substr(first);

        if (line.empty() || line[0] == '#' || line.rfind("```", 0) == 0 || line.rfind("$$", 0) == 0 || (line.length() >= 3 && (line.find_first_not_of('-') == std::string::npos || line.find_first_not_of('*') == std::string::npos))) {
            continue;
        }
        summary.append(line).append(" ");
    }

    if (summary.length() > 150) {
        size_t cut_pos = 0;
        int char_count = 0;
        const int char_limit = 75;
        for (size_t i = 0; i < summary.length() && char_count < char_limit; ++i) {
            if ((summary[i] & 0xC0) != 0x80) { 
                char_count++;
            }
            cut_pos = i + 1;
        }
        summary = summary.substr(0, cut_pos);
    }
    return summary;
}

void process_single_file() {
    std::string title, content_filename, output_filename, tags_input;
    std::cout << "请输入文章标题: ";
    std::getline(std::cin, title);
    std::cout << "请输入内容文件名 (例如: content.txt): ";
    std::getline(std::cin, content_filename);
    std::cout << "请输入输出HTML文件名 (例如: article.html): ";
    std::getline(std::cin, output_filename);
    std::cout << "请输入文章标签 (用逗号分隔): ";
    std::getline(std::cin, tags_input);

    std::ifstream content_file(content_filename);
    if (!content_file) {
        std::cerr << "错误: 无法打开内容文件 '" << content_filename << "'\n";
        return;
    }

    std::string parsed_content = parse_content_to_html(content_file);
    content_file.close();

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = localtime_safe(in_time_t);
    char date_buffer[128];
    strftime(date_buffer, sizeof(date_buffer), "%Y年%m月%d日", &local_tm);
    std::string date_str(date_buffer);

    std::stringstream tags_ss(tags_input);
    std::string tag, first_tag, category_html;
    std::stringstream tags_html_ss;
    std::vector<std::string> colors = {"indigo", "purple", "pink", "green", "blue", "yellow", "red"};
    int color_index = 0;

    while (std::getline(tags_ss, tag, ',')) {
        size_t first = tag.find_first_not_of(" \t");
        if (std::string::npos == first) continue;
        size_t last = tag.find_last_not_of(" \t");
        tag = tag.substr(first, (last - first + 1));
        if (!tag.empty()) {
            if (first_tag.empty()) first_tag = tag;
            const std::string& color = colors[color_index % colors.size()];
            tags_html_ss << "<a href=\"#\" class=\"bg-" << color << "-100 text-" << color << "-800 text-sm font-medium px-3 py-1 rounded-full hover:bg-" << color << "-200 transition-colors\">" << escape_html(tag) << "</a>\n";
            color_index++;
        }
    }
    category_html = "<span>分类：<a href=\"#\" class=\"text-purple-600 hover:underline\">" + escape_html(first_tag.empty() ? "未分类" : first_tag) + "</a></span>";
    
    std::string final_html = HTML_TEMPLATE;
    replace_all(final_html, "<!--TITLE_PLACEHOLDER-->", escape_html(title));
    replace_all(final_html, "<!--DATE_PLACEHOLDER-->", date_str);
    replace_all(final_html, "<!--CONTENT_PLACEHOLDER-->", parsed_content);
    replace_all(final_html, "<!--TAGS_PLACEHOLDER-->", tags_html_ss.str());
    replace_all(final_html, "<!--CATEGORY_PLACEHOLDER-->", category_html);

    std::ofstream output_file(output_filename);
    if (!output_file) { std::cerr << "错误: 无法创建输出文件 '" << output_filename << "'\n"; return; }
    output_file << final_html;
    output_file.close();
    std::cout << "\n成功! 文章HTML文件已生成: " << output_filename << std::endl;
}

void process_batch() {
    std::string text_dir = "text";
    std::vector<std::string> txt_files = list_txt_files(text_dir);

    if (txt_files.empty()) {
        std::cout << "在 '" << text_dir << "' 文件夹中未找到任何 .txt 文件。\n";
        return;
    }

    std::cout << "找到了 " << txt_files.size() << " 个 .txt 文件。开始批量处理...\n\n";
    std::string default_tags;
    std::cout << "请输入所有文章的默认标签 (用逗号分隔，可留空): ";
    std::getline(std::cin, default_tags);

    std::stringstream all_previews_ss;
    
    for (const auto& filename : txt_files) {
        std::string full_path = text_dir + "/" + filename;
        std::ifstream content_file(full_path);
        if (!content_file) {
            std::cerr << "错误: 无法打开 " << full_path << "，已跳过。\n";
            continue;
        }

        std::string title;
        std::getline(content_file, title);
        if (title.empty()) { title = filename; }
        
        std::stringstream content_ss;
        content_ss << content_file.rdbuf();
        std::string full_content_string = content_ss.str();
        content_file.close();

        std::istringstream content_to_parse(full_content_string);
        std::string parsed_content = parse_content_to_html(content_to_parse);

        std::string base_filename = filename.substr(0, filename.length() - 4);
        std::string output_filename = base_filename + ".html";

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = localtime_safe(in_time_t);
        char date_buffer[128];
        strftime(date_buffer, sizeof(date_buffer), "%Y年%m月%d日", &local_tm);
        std::string date_str(date_buffer);

        std::stringstream tags_ss(default_tags);
        std::string tag, first_tag, category_html;
        std::stringstream tags_html_ss;
        std::vector<std::string> colors = {"indigo", "purple", "pink", "green", "blue", "yellow", "red"};
        int color_index = 0;
        
        while (std::getline(tags_ss, tag, ',')) {
            size_t first = tag.find_first_not_of(" \t");
            if (std::string::npos == first) continue;
            size_t last = tag.find_last_not_of(" \t");
            tag = tag.substr(first, (last - first + 1));
            if (!tag.empty()) {
                if (first_tag.empty()) first_tag = tag;
                const std::string& color = colors[color_index % colors.size()];
                tags_html_ss << "<a href=\"#\" class=\"bg-" << color << "-100 text-" << color << "-800 text-sm font-medium px-3 py-1 rounded-full hover:bg-" << color << "-200 transition-colors\">" << escape_html(tag) << "</a>\n";
                color_index++;
            }
        }
        category_html = "<span>分类：<a href=\"#\" class=\"text-purple-600 hover:underline\">" + escape_html(first_tag.empty() ? "未分类" : first_tag) + "</a></span>";

        std::string final_html = HTML_TEMPLATE;
        replace_all(final_html, "<!--TITLE_PLACEHOLDER-->", escape_html(title));
        replace_all(final_html, "<!--DATE_PLACEHOLDER-->", date_str);
        replace_all(final_html, "<!--CONTENT_PLACEHOLDER-->", parsed_content);
        replace_all(final_html, "<!--TAGS_PLACEHOLDER-->", tags_html_ss.str());
        replace_all(final_html, "<!--CATEGORY_PLACEHOLDER-->", category_html);

        std::ofstream output_file(output_filename);
        if (!output_file) {
            std::cerr << "错误: 无法创建 " << output_filename << "，已跳过。\n";
            continue;
        }
        output_file << final_html;
        output_file.close();
        
        std::string summary = create_summary(full_content_string);
        all_previews_ss << generate_preview_html(title, summary, date_str, first_tag.empty() ? "未分类" : first_tag, output_filename);

        std::cout << "  - 已成功生成: " << output_filename << "\n";
    }

    std::string preview_filename = "`[pre-index]previews_for_index.html";
    std::ofstream preview_file(preview_filename);
    preview_file << all_previews_ss.str();
    preview_file.close();

    std::cout << "\n批量处理完成！\n";
    std::cout << "所有文章预览代码已保存至: " << preview_filename << "\n";
}


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    char mode;
    std::cout << "请选择运行模式:\n";
    std::cout << "  1. 单文件模式 (手动输入信息)\n";
    std::cout << "  2. 批量处理模式 (自动处理 'text' 文件夹下的所有 .txt 文件)\n";
    std::cout << "请输入模式编号 (1 或 2): ";
    std::cin >> mode;
    std::cin.ignore(10000, '\n'); // Clear the input buffer

    if (mode == '1') {
        process_single_file();
    } else if (mode == '2') {
        process_batch();
    } else {
        std::cout << "无效的模式选择。\n";
    }

    return 0;
}