#include "KQueueListener.h"
#include "LoggingListener.h"

#include <iostream>

#include "GumboHtmlParser.h"
#include <iostream>

int main() {
  const std::string html = R"HTML(<div id="aarecord-list">
              <script>
    // We can't do this in Jinja because of https://github.com/pallets/jinja/issues/1693 :(
    if (!window.aarecord_list_code_loaded) {
      window.aarecord_list_code_loaded = true;

      var lastAnimationFrame = undefined;
      var topByElement = new Map();
      function render() {
        window.cancelAnimationFrame(lastAnimationFrame);
        lastAnimationFrame = window.requestAnimationFrame(() => {
          var bottomEdge = window.scrollY + window.innerHeight * 3; // Load 3 pages worth
          for (element of document.querySelectorAll('.js-scroll-hidden')) {
            if (!topByElement.get(element)) {
              topByElement.set(element, element.getBoundingClientRect().top + window.scrollY);
            }
            if (topByElement.get(element) <= bottomEdge) {
              element.classList.remove("js-scroll-hidden");
              element.innerHTML = element.innerHTML.replace('<' + '!--', '').replace('-' + '->', '')
            }
          }
        });
      }
      document.addEventListener('DOMContentLoaded', () => {
        document.addEventListener('scroll', () => {
          render();
        });
        render();
      });

      document.addEventListener("keydown", e => {
        const fields = Array.from(document.querySelectorAll('.js-vim-focus'));
        if (fields.length === 0) {
          return;
        }

        if (e.ctrlKey || e.metaKey || e.altKey) return;
        if (/^(?:input|textarea|select|button)$/i.test(e.target.tagName)) {
          if (e.key === "Escape") {
            e.preventDefault();
            fields[0].focus();
            return;
          }
          return;
        }
        if (e.key === "j" || e.key === "k") {
          e.preventDefault();
          const activeIndex = fields.indexOf(document.activeElement);
          if (activeIndex === -1) {
            fields[0].focus();
          } else {
            if (e.key === "j") {
              const newIndex = Math.min(activeIndex+1, fields.length-1);
              fields[newIndex].focus();
            } else {
              const newIndex = Math.max(activeIndex-1, 0);
              fields[newIndex].focus();
            }
          }
        }
      });
    }
  </script>



    <table class="text-sm w-full mt-4 h-fit">
        <tbody><tr class="group h-full even:bg-[#f2f2f2] hover:bg-yellow-100 aria-selected:bg-yellow-100 cursor-pointer relative ">
          <td class="h-full w-[22px]">
            <a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px">
                <span class="absolute left-0 top-[50%] hidden group-hover:block group-aria-selected:block">
                  <div id="hover_cover_aarecord_id__md5:3e803cb24585957ac75f27d82f8df4c2" class="absolute right-1 top-0 min-w-[170px] -translate-y-1/2 group-hover:z-30 group-aria-selected:z-20 shadow-xl">
                    <img class="min-w-[170px]" src="https://s3proxy.cdn-zlib.sk//covers299/collections/userbooks/30e516e0e85f0672cdd3b701d9b05cd104ae2b77c0e3ac0ed8a17d6a3b979139.jpg" alt="" referrerpolicy="no-referrer" onerror="this.parentNode.removeChild(this)" loading="lazy" decoding="async">
                  </div>
                </span>

              <span id="table_cover_aarecord_id__md5:3e803cb24585957ac75f27d82f8df4c2" class="relative overflow-hidden w-[22px] h-[30px] flex flex-col justify-center">

                  <img class="relative inline-block" src="https://s3proxy.cdn-zlib.sk//covers299/collections/userbooks/30e516e0e85f0672cdd3b701d9b05cd104ae2b77c0e3ac0ed8a17d6a3b979139.jpg" alt="" referrerpolicy="no-referrer" onerror="this.parentNode.removeChild(this)" onload="for (let el of document.querySelectorAll('.js-img-background-0e08f5732edb4f1b4eba4eaa6e31b4f8')) { el.parentNode.removeChild(el); }" loading="lazy" decoding="async">
              </span>
            </a>

            <a href="/md5/3e803cb24585957ac75f27d82f8df4c2" class="js-vim-focus custom-a absolute w-full h-full top-0 left-0 outline-offset-[-2px] outline-2 rounded-[3px] focus:outline pointer-events-none z-10" onfocus="this.parentNode.parentNode.setAttribute('aria-selected', 'true')" onblur="this.parentNode.parentNode.setAttribute('aria-selected', 'false')"></a>
          </td>
          <td class="h-full w-[18%]"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">Stoner</span></a></td>
          <td class="h-full w-[18%]"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">John Williams, John Williams</span></a></td>
          <td class="h-full w-[18%]"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">Vintage (UK), 1965<span class="block text-xs text-gray-500">Vintage/Ebury (a Division of Random</span><span class="block text-xs text-gray-500">Constable and Robinson</span><span class="block text-xs text-gray-500">Vintage Digital</span><span class="block text-xs text-gray-500">United Kingdom and Ireland, United Kingdom</span><span class="block text-xs text-gray-500">Vintage classics, London, 2003</span><span class="block text-xs text-gray-500">February 6, 2003</span></span></a></td>
          <td class="h-full"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">1965<span class="block text-xs text-gray-500">2003</span></span></a></td>
          <td class="h-full w-[18%] max-w-[25%] text-xs"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100"></span></a></td>
          <td class="h-full text-xs"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100"><wbr>/zlib</span></a></td>
          <td class="h-full text-xs"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">en</span></a></td>
          <td class="h-full text-xs"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">Book (unknown)</span></a></td>
          <td class="h-full text-xs"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">epub</span></a></td>
          <td class="h-full text-xs"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">0.3MB</span></a></td>
          <td class="h-full text-xs"><a href="/md5/3e803cb24585957ac75f27d82f8df4c2" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100"></span></a></td>
        </tr>
        <tr class="group h-full even:bg-[#f2f2f2] hover:bg-yellow-100 aria-selected:bg-yellow-100 cursor-pointer relative ">
          <td class="h-full w-[22px]">
            <a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px">
                <span class="absolute left-0 top-[50%] hidden group-hover:block group-aria-selected:block">
                  <div id="hover_cover_aarecord_id__md5:614b40bb8b43f6e4a7614150ae087f58" class="absolute right-1 top-0 min-w-[170px] -translate-y-1/2 group-hover:z-30 group-aria-selected:z-20 shadow-xl">
                    <img class="min-w-[170px]" src="https://s3proxy.cdn-zlib.sk//covers299/collections/userbooks/4ab5250b781b9f8ff4f894b4355a86a8ff01bd745fd8eaad9074cc5c125f6593.jpg" alt="" referrerpolicy="no-referrer" onerror="this.parentNode.removeChild(this)" loading="lazy" decoding="async">
                  </div>
                </span>

              <span id="table_cover_aarecord_id__md5:614b40bb8b43f6e4a7614150ae087f58" class="relative overflow-hidden w-[22px] h-[30px] flex flex-col justify-center">

                  <img class="relative inline-block" src="https://s3proxy.cdn-zlib.sk//covers299/collections/userbooks/4ab5250b781b9f8ff4f894b4355a86a8ff01bd745fd8eaad9074cc5c125f6593.jpg" alt="" referrerpolicy="no-referrer" onerror="this.parentNode.removeChild(this)" onload="for (let el of document.querySelectorAll('.js-img-background-10666c41b6b2338c1d7a6c85376eedf1')) { el.parentNode.removeChild(el); }" loading="lazy" decoding="async">
              </span>
            </a>

            <a href="/md5/614b40bb8b43f6e4a7614150ae087f58" class="js-vim-focus custom-a absolute w-full h-full top-0 left-0 outline-offset-[-2px] outline-2 rounded-[3px] focus:outline pointer-events-none z-10" onfocus="this.parentNode.parentNode.setAttribute('aria-selected', 'true')" onblur="this.parentNode.parentNode.setAttribute('aria-selected', 'false')"></a>
          </td>
          <td class="h-full w-[18%]"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">Stoner</span></a></td>
          <td class="h-full w-[18%]"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">John Williams</span></a></td>
          <td class="h-full w-[18%]"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">New York Review Books, 2013</span></a></td>
          <td class="h-full"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">2013</span></a></td>
          <td class="h-full w-[18%] max-w-[25%] text-xs"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100"></span></a></td>
          <td class="h-full text-xs"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100"><wbr>/zlib</span></a></td>
          <td class="h-full text-xs"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">en</span></a></td>
          <td class="h-full text-xs"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">Book (unknown)</span></a></td>
          <td class="h-full text-xs"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">epub</span></a></td>
          <td class="h-full text-xs"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100">0.4MB</span></a></td>
          <td class="h-full text-xs"><a href="/md5/614b40bb8b43f6e4a7614150ae087f58" tabindex="-1" aria-disabled="true" style="overflow-wrap: break-word; max-height: 92px; border-top: 1px solid transparent; border-bottom: 1px solid transparent; --darkreader-inline-border-top: transparent; --darkreader-inline-border-bottom: transparent;" class="custom-a flex flex-col h-full px-[0.5px] justify-around overflow-hidden group-hover:overflow-visible group-hover:relative group-hover:z-30 group-aria-selected:overflow-visible group-aria-selected:relative group-aria-selected:z-20" data-darkreader-inline-border-top="" data-darkreader-inline-border-bottom=""><span class="group-hover:bg-yellow-100 group-aria-selected:bg-yellow-100"></span></a></td>
        </tr>
    </tbody></table>



            </div>
  )HTML";

  return 0;
};

// int main()
// {
//   KQueueListener kq;
//   LoggingListener ll;

//   kq.AddListener(&ll);
//   std::string dir = std::string(std::getenv("HOME")) + "/KQueueListenerTest";
//   kq.WatchDir(dir);

//   kq.Start();

//   std::cout << "Watching " << dir << "\n- press <Ctrl+C> to quit.\n";
//   std::cin.get();

//   kq.Stop();
//   std::cout << "Stopped.\n";
//   return 0;
// };
