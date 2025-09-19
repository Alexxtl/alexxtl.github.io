#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstring>

// 如果是Windows系统，则包含windows.h并自动设置控制台编码
#ifdef _WIN32
#include <windows.h>
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
    
    <!-- MathJax 配置脚本，必须在加载 MathJax 主脚本之前 -->
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
        /* 为行内代码块添加样式 */
        :not(pre) > code {
            background-color: #f3f4f6; /* bg-gray-100 */
            color: #be123c; /* text-rose-700 */
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

// 帮助函数：替换字符串中所有出现的占位符
void replace_all(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

// 帮助函数：转义HTML特殊字符
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

// 跨平台安全地获取本地时间
std::tm localtime_safe(const std::time_t& t) {
    std::tm tm_snapshot;
#if defined(_MSC_VER)
    localtime_s(&tm_snapshot, &t);
#else
    // 对于GCC/Clang等其他编译器，使用 localtime_r
    localtime_r(&t, &tm_snapshot);
#endif
    return tm_snapshot;
}

// --- 重构的 Markdown 解析函数 ---

// 帮助函数：处理行内元素，如代码、加粗和链接
std::string parse_inline_elements(std::string line) {
    std::string result = "";
    size_t last_pos = 0;

    while (last_pos < line.length()) {
        // 查找下一个特殊字符
        size_t code_pos = line.find('`', last_pos);
        size_t bold_pos = line.find("**", last_pos);
        size_t link_pos = line.find('[', last_pos);

        // 确定最先出现的特殊字符
        size_t next_pos = std::string::npos;
        if (code_pos != std::string::npos) next_pos = std::min(next_pos, code_pos);
        if (bold_pos != std::string::npos) next_pos = std::min(next_pos, bold_pos);
        if (link_pos != std::string::npos) next_pos = std::min(next_pos, link_pos);

        // 如果没有更多特殊字符，则添加剩余文本并结束
        if (next_pos == std::string::npos) {
            result += line.substr(last_pos);
            break;
        }

        // 添加特殊字符前的普通文本
        result += line.substr(last_pos, next_pos - last_pos);
        last_pos = next_pos;

        // --- 根据找到的特殊字符进行处理 ---

        // 处理行内代码 `...`
        if (next_pos == code_pos) {
            size_t end_pos = line.find('`', last_pos + 1);
            if (end_pos != std::string::npos) {
                std::string code_content = line.substr(last_pos + 1, end_pos - last_pos - 1);
                result += "<code>" + escape_html(code_content) + "</code>";
                last_pos = end_pos + 1;
            } else {
                result += '`'; // 未找到闭合标签，当作普通字符处理
                last_pos++;
            }
        }
        // 处理加粗 **...**
        else if (next_pos == bold_pos) {
            size_t end_pos = line.find("**", last_pos + 2);
            if (end_pos != std::string::npos) {
                std::string bold_content = line.substr(last_pos + 2, end_pos - last_pos - 2);
                result += "<strong>" + parse_inline_elements(bold_content) + "</strong>"; // 递归处理内部元素
                last_pos = end_pos + 2;
            } else {
                result += "**"; // 未找到闭合标签
                last_pos += 2;
            }
        }
        // 处理链接 [...]...
        else if (next_pos == link_pos) {
            size_t link_end = line.find("]", last_pos);
            size_t url_start = line.find("(", link_end);
            size_t url_end = line.find(")", url_start);

            if (link_end != std::string::npos && url_start == link_end + 1 && url_end != std::string::npos) {
                std::string text = line.substr(last_pos + 1, link_end - last_pos - 1);
                std::string url = line.substr(url_start + 1, url_end - url_start - 1);
                result += "<a href=\"" + url + "\" class=\"text-indigo-600 hover:underline\" target=\"_blank\">" + parse_inline_elements(text) + "</a>";
                last_pos = url_end + 1;
            } else {
                result += '['; // 不是有效的链接格式
                last_pos++;
            }
        }
    }
    return result;
}

// 主解析函数：将Markdown内容转换为HTML
std::string parse_content_to_html(std::istream& input) {
    std::stringstream output;
    std::string line;
    bool in_code_block = false;
    bool in_list = false;

    while (std::getline(input, line)) {
        // --- 代码块处理 ---
        if (line.rfind("```cpp", 0) == 0) {
            if (in_list) { output << "</ul>\n"; in_list = false; }
            in_code_block = true;
            output << "<pre><code class=\"language-cpp\">";
            continue;
        }
        if (line.rfind("```", 0) == 0 && in_code_block) {
            in_code_block = false;
            output << "</code></pre>\n";
            continue;
        }
        if (in_code_block) {
            output << escape_html(line) << "\n";
            continue;
        }

        // --- 块级元素处理 ---

        // 标题
        if (line.rfind("## ", 0) == 0) {
            if (in_list) { output << "</ul>\n"; in_list = false; }
            output << "<h2 class=\"text-2xl font-bold mt-8 mb-4\">" << line.substr(3) << "</h2>\n";
        } 
        // 列表
        else if (line.rfind("- ", 0) == 0) {
            if (!in_list) { output << "<ul class=\"list-disc pl-5 my-4\">\n"; in_list = true; }
            std::string item_content = line.substr(2);
            output << "<li>" << parse_inline_elements(item_content) << "</li>\n";
        } 
        // 空行
        else if (line.empty()) {
            if (in_list) { output << "</ul>\n"; in_list = false; }
        } 
        // 普通段落
        else {
            if (in_list) { output << "</ul>\n"; in_list = false; }
            output << "<p>" << parse_inline_elements(line) << "</p>\n";
        }
    }
    if (in_list) { output << "</ul>\n"; } // 确保关闭最后的列表

    return output.str();
}


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::string title, content_filename, output_filename, tags_input;

    std::cout << "请输入文章标题: ";
    std::getline(std::cin, title);

    std::cout << "请输入内容文件名 (例如: content.txt): ";
    std::getline(std::cin, content_filename);

    std::cout << "请输入输出HTML文件名 (例如: article.html): ";
    std::getline(std::cin, output_filename);

    std::cout << "请输入文章标签 (用逗号分隔, 例如: C++,算法,题解): ";
    std::getline(std::cin, tags_input);


    std::ifstream content_file(content_filename);
    if (!content_file.is_open()) {
        std::cerr << "错误: 无法打开内容文件 '" << content_filename << "'" << std::endl;
        return 1;
    }

    // 解析内容
    std::string parsed_content = parse_content_to_html(content_file);
    content_file.close();

    // 获取当前日期
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = localtime_safe(in_time_t);
    
    char date_buffer[128];
    if (strftime(date_buffer, sizeof(date_buffer), "%Y年%m月%d日", &local_tm)) {
        // 成功
    } else {
        strcpy(date_buffer, "日期获取失败");
    }
    std::string date_str(date_buffer);

    // --- 生成标签和分类的HTML ---
    std::stringstream tags_ss(tags_input);
    std::string tag;
    std::stringstream tags_html_ss;
    std::string first_tag = "";
    std::vector<std::string> colors = {"indigo", "purple", "pink", "green", "blue", "yellow", "red"};
    int color_index = 0;

    while (std::getline(tags_ss, tag, ',')) {
        size_t first = tag.find_first_not_of(" \t");
        if (std::string::npos == first) continue;
        size_t last = tag.find_last_not_of(" \t");
        tag = tag.substr(first, (last - first + 1));

        if (!tag.empty()) {
            if (first_tag.empty()) {
                first_tag = tag;
            }
            const std::string& color = colors[color_index % colors.size()];
            tags_html_ss << "<a href=\"#\" class=\"bg-" << color << "-100 text-" << color << "-800 text-sm font-medium px-3 py-1 rounded-full hover:bg-" << color << "-200 transition-colors\">" << escape_html(tag) << "</a>\n";
            color_index++;
        }
    }

    std::string category_html;
    if (first_tag.empty()) {
        category_html = "<span>分类：<a href=\"#\" class=\"text-purple-600 hover:underline\">未分类</a></span>";
    } else {
        category_html = "<span>分类：<a href=\"#\" class=\"text-purple-600 hover:underline\">" + escape_html(first_tag) + "</a></span>";
    }

    // 填充模板
    std::string final_html = HTML_TEMPLATE;
    replace_all(final_html, "<!--TITLE_PLACEHOLDER-->", escape_html(title));
    replace_all(final_html, "<!--DATE_PLACEHOLDER-->", date_str);
    replace_all(final_html, "<!--CONTENT_PLACEHOLDER-->", parsed_content);
    replace_all(final_html, "<!--TAGS_PLACEHOLDER-->", tags_html_ss.str());
    replace_all(final_html, "<!--CATEGORY_PLACEHOLDER-->", category_html);

    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "错误: 无法创建输出文件 '" << output_filename << "'" << std::endl;
        return 1;
    }

    output_file << final_html;
    output_file.close();

    std::cout << "\n成功! 文章HTML文件已生成: " << output_filename << std::endl;

    return 0;
}

