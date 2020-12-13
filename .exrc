if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <C-_>9 <Plug>TComment_9
imap <C-_>8 <Plug>TComment_8
imap <C-_>7 <Plug>TComment_7
imap <C-_>6 <Plug>TComment_6
imap <C-_>5 <Plug>TComment_5
imap <C-_>4 <Plug>TComment_4
imap <C-_>3 <Plug>TComment_3
imap <C-_>2 <Plug>TComment_2
imap <C-_>1 <Plug>TComment_1
imap <C-_>s <Plug>TComment_s
imap <C-_>n <Plug>TComment_n
imap <C-_>a <Plug>TComment_a
imap <C-_>b <Plug>TComment_b
imap <C-_>i <Plug>TComment_i
imap <C-_>r <Plug>TComment_r
imap <C-_>  <Plug>TComment_ 
imap <C-_>p <Plug>TComment_p
imap <C-_><C-_> <Plug>TComment_
inoremap <Plug>TComment_<C-_>9 :call tcomment#SetOption("count", 9)
inoremap <Plug>TComment_9 :call tcomment#SetOption("count", 9)
inoremap <Plug>TComment_<C-_>8 :call tcomment#SetOption("count", 8)
inoremap <Plug>TComment_8 :call tcomment#SetOption("count", 8)
inoremap <Plug>TComment_<C-_>7 :call tcomment#SetOption("count", 7)
inoremap <Plug>TComment_7 :call tcomment#SetOption("count", 7)
inoremap <Plug>TComment_<C-_>6 :call tcomment#SetOption("count", 6)
inoremap <Plug>TComment_6 :call tcomment#SetOption("count", 6)
inoremap <Plug>TComment_<C-_>5 :call tcomment#SetOption("count", 5)
inoremap <Plug>TComment_5 :call tcomment#SetOption("count", 5)
inoremap <Plug>TComment_<C-_>4 :call tcomment#SetOption("count", 4)
inoremap <Plug>TComment_4 :call tcomment#SetOption("count", 4)
inoremap <Plug>TComment_<C-_>3 :call tcomment#SetOption("count", 3)
inoremap <Plug>TComment_3 :call tcomment#SetOption("count", 3)
inoremap <Plug>TComment_<C-_>2 :call tcomment#SetOption("count", 2)
inoremap <Plug>TComment_2 :call tcomment#SetOption("count", 2)
inoremap <Plug>TComment_<C-_>1 :call tcomment#SetOption("count", 1)
inoremap <Plug>TComment_1 :call tcomment#SetOption("count", 1)
inoremap <Plug>TComment_<C-_>s :TCommentAs =&ft_
inoremap <Plug>TComment_s :TCommentAs =&ft_
inoremap <Plug>TComment_<C-_>n :TCommentAs =&ft 
inoremap <Plug>TComment_n :TCommentAs =&ft 
inoremap <Plug>TComment_<C-_>a :TCommentAs 
inoremap <Plug>TComment_a :TCommentAs 
inoremap <Plug>TComment_<C-_>b :TCommentBlock mode=#
inoremap <Plug>TComment_b :TCommentBlock mode=#
inoremap <Plug>TComment_<C-_>i v:TCommentInline mode=#
inoremap <Plug>TComment_i v:TCommentInline mode=#
inoremap <Plug>TComment_<C-_>r :TCommentRight
inoremap <Plug>TComment_r :TCommentRight
inoremap <Plug>TComment_<C-_>  :TComment 
inoremap <Plug>TComment_  :TComment 
inoremap <Plug>TComment_<C-_>p :norm! m`vip:TComment``
inoremap <Plug>TComment_p :norm! m`vip:TComment``
inoremap <Plug>TComment_<C-_><C-_> :TComment
inoremap <Plug>TComment_ :TComment
imap <C-Y>m <Plug>(emmet-merge-lines)
inoremap <Plug>(emmet-merge-lines) =emmet#util#closePopup()=emmet#mergeLines()
imap <C-Y>A <Plug>(emmet-anchorize-summary)
inoremap <Plug>(emmet-anchorize-summary) =emmet#util#closePopup()=emmet#anchorizeURL(1)
imap <C-Y>a <Plug>(emmet-anchorize-url)
inoremap <Plug>(emmet-anchorize-url) =emmet#util#closePopup()=emmet#anchorizeURL(0)
imap <C-Y>k <Plug>(emmet-remove-tag)
inoremap <Plug>(emmet-remove-tag) =emmet#util#closePopup()=emmet#removeTag()
imap <C-Y>j <Plug>(emmet-split-join-tag)
inoremap <Plug>(emmet-split-join-tag) :call emmet#splitJoinTag()
imap <C-Y>/ <Plug>(emmet-toggle-comment)
inoremap <Plug>(emmet-toggle-comment) =emmet#util#closePopup()=emmet#toggleComment()
imap <C-Y>I <Plug>(emmet-image-encode)
inoremap <Plug>(emmet-image-encode) =emmet#util#closePopup()=emmet#imageEncode()
imap <C-Y>i <Plug>(emmet-image-size)
inoremap <Plug>(emmet-image-size) =emmet#util#closePopup()=emmet#imageSize()
inoremap <Plug>(emmet-move-prev-item) :call emmet#moveNextPrevItem(1)
inoremap <Plug>(emmet-move-next-item) :call emmet#moveNextPrevItem(0)
imap <C-Y>N <Plug>(emmet-move-prev)
inoremap <Plug>(emmet-move-prev) =emmet#util#closePopup()=emmet#moveNextPrev(1)
imap <C-Y>n <Plug>(emmet-move-next)
inoremap <Plug>(emmet-move-next) =emmet#util#closePopup()=emmet#moveNextPrev(0)
imap <C-Y>D <Plug>(emmet-balance-tag-outword)
inoremap <Plug>(emmet-balance-tag-outword) :call emmet#balanceTag(-1)
imap <C-Y>d <Plug>(emmet-balance-tag-inward)
inoremap <Plug>(emmet-balance-tag-inward) :call emmet#balanceTag(1)
imap <C-Y>u <Plug>(emmet-update-tag)
inoremap <Plug>(emmet-update-tag) =emmet#util#closePopup()=emmet#updateTag()
imap <C-Y>; <Plug>(emmet-expand-word)
inoremap <Plug>(emmet-expand-word) =emmet#util#closePopup()=emmet#expandAbbr(1,"")
imap <C-Y>, <Plug>(emmet-expand-abbr)
inoremap <Plug>(emmet-expand-abbr) =emmet#util#closePopup()=emmet#expandAbbr(0,"")
inoremap <silent> <C-[>OC <Right>
inoremap <silent> <C-Tab> =UltiSnips#ListSnippets()
imap <C-@> 
imap <Nul> 
imap <silent> <C-F> X:call MyKeyMapHighlight()a
cmap <silent> <C-F> 
imap <PageDown> 
imap <PageUp> 
imap <F5> :q
imap <F4> :w!
imap <F3> :nohlsearch
imap <F2> :TagbarToggle
imap <F1> :WMToggle
cmap <C-L> <Del>
cmap <C-K> <Right>
cmap <C-J> <Left>
imap <C-L> <Del>
imap <C-K> <Right>
imap <C-J> <Left>
vmap <silent>  a:call MyKeyMapHighlight()gv
nmap <silent>  a:call MyKeyMapHighlight()
snoremap <silent>  c
nmap  5h
xnoremap <silent> 	 :call UltiSnips#SaveLastVisualSelection()gvs
snoremap <silent> 	 :call UltiSnips#ExpandSnippet()
nmap <NL> 5j
nmap  5k
nmap  5l
snoremap  "_c
vmap c <Plug>(emmet-code-pretty)
nmap m <Plug>(emmet-merge-lines)
nmap A <Plug>(emmet-anchorize-summary)
nmap a <Plug>(emmet-anchorize-url)
nmap k <Plug>(emmet-remove-tag)
nmap j <Plug>(emmet-split-join-tag)
nmap / <Plug>(emmet-toggle-comment)
nmap I <Plug>(emmet-image-encode)
nmap i <Plug>(emmet-image-size)
nmap N <Plug>(emmet-move-prev)
nmap n <Plug>(emmet-move-next)
vmap D <Plug>(emmet-balance-tag-outword)
nmap D <Plug>(emmet-balance-tag-outword)
vmap d <Plug>(emmet-balance-tag-inward)
nmap d <Plug>(emmet-balance-tag-inward)
nmap u <Plug>(emmet-update-tag)
nmap ; <Plug>(emmet-expand-word)
vmap , <Plug>(emmet-expand-abbr)
nmap , <Plug>(emmet-expand-abbr)
vmap 9 <Plug>TComment_9
nmap 9 <Plug>TComment_9
omap 9 <Plug>TComment_9
vmap 8 <Plug>TComment_8
nmap 8 <Plug>TComment_8
omap 8 <Plug>TComment_8
vmap 7 <Plug>TComment_7
nmap 7 <Plug>TComment_7
omap 7 <Plug>TComment_7
vmap 6 <Plug>TComment_6
nmap 6 <Plug>TComment_6
omap 6 <Plug>TComment_6
vmap 5 <Plug>TComment_5
nmap 5 <Plug>TComment_5
omap 5 <Plug>TComment_5
vmap 4 <Plug>TComment_4
nmap 4 <Plug>TComment_4
omap 4 <Plug>TComment_4
vmap 3 <Plug>TComment_3
nmap 3 <Plug>TComment_3
omap 3 <Plug>TComment_3
vmap 2 <Plug>TComment_2
nmap 2 <Plug>TComment_2
omap 2 <Plug>TComment_2
vmap 1 <Plug>TComment_1
nmap 1 <Plug>TComment_1
omap 1 <Plug>TComment_1
map ca <Plug>TComment_ca
map cc <Plug>TComment_cc
map s <Plug>TComment_s
map n <Plug>TComment_n
map a <Plug>TComment_a
map b <Plug>TComment_b
map i <Plug>TComment_i
map r <Plug>TComment_r
map   <Plug>TComment_ 
map p <Plug>TComment_p
vmap  <Plug>TComment_
nmap  <Plug>TComment_
omap  <Plug>TComment_
nmap ,S :call MySwitchToSourceInNewWindow()
nmap ,s :call MySwitchToSource()
nmap ,H :call MySwitchToHeaderInNewWindow()
nmap ,h :call MySwitchToHeader()
nmap ,l :clist
nmap ,p :cprevious
nmap ,n :cnext
nmap ,w :cwindow
nmap ,m :call MyMake()
map - $a -->
map \_s <Plug>TComment_\_s
map \_n <Plug>TComment_\_n
map \_a <Plug>TComment_\_a
map \_b <Plug>TComment_\_b
map \_r <Plug>TComment_\_r
xmap \_i <Plug>TComment_\_i
map \_  <Plug>TComment_\_ 
map \_p <Plug>TComment_\_p
xmap \__ <Plug>TComment_\__
nmap \__ <Plug>TComment_\__
smap \__ <Plug>TComment_\__
omap \__ <Plug>TComment_\__
nmap <silent> \cc :ErrorAtCursor
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
xmap g> <Plug>TComment_Comment
nmap <silent> g>b <Plug>TComment_Commentb
nmap <silent> g>c <Plug>TComment_Commentc
nmap <silent> g> <Plug>TComment_Comment
xmap g< <Plug>TComment_Uncomment
nmap <silent> g<b <Plug>TComment_Uncommentb
nmap <silent> g<c <Plug>TComment_Uncommentc
nmap <silent> g< <Plug>TComment_Uncomment
xmap gc <Plug>TComment_gc
nmap <silent> gcb <Plug>TComment_gcb
nmap <silent> gcc <Plug>TComment_gcc
nmap <silent> gc9c <Plug>TComment_gc9c
nmap <silent> gc9 <Plug>TComment_gc9
nmap <silent> gc8c <Plug>TComment_gc8c
nmap <silent> gc8 <Plug>TComment_gc8
nmap <silent> gc7c <Plug>TComment_gc7c
nmap <silent> gc7 <Plug>TComment_gc7
nmap <silent> gc6c <Plug>TComment_gc6c
nmap <silent> gc6 <Plug>TComment_gc6
nmap <silent> gc5c <Plug>TComment_gc5c
nmap <silent> gc5 <Plug>TComment_gc5
nmap <silent> gc4c <Plug>TComment_gc4c
nmap <silent> gc4 <Plug>TComment_gc4
nmap <silent> gc3c <Plug>TComment_gc3c
nmap <silent> gc3 <Plug>TComment_gc3
nmap <silent> gc2c <Plug>TComment_gc2c
nmap <silent> gc2 <Plug>TComment_gc2
nmap <silent> gc1c <Plug>TComment_gc1c
nmap <silent> gc1 <Plug>TComment_gc1
nmap <silent> gc <Plug>TComment_gc
omap ic <Plug>TComment_ic
vmap ic <Plug>TComment_ic
noremap <silent> <Plug>AirlineSelectNextTab :exe repeat(':tabn|', v:count1)
noremap <silent> <Plug>AirlineSelectPrevTab gT
noremap <silent> <Plug>AirlineSelectTab9 :9tabn
noremap <silent> <Plug>AirlineSelectTab8 :8tabn
noremap <silent> <Plug>AirlineSelectTab7 :7tabn
noremap <silent> <Plug>AirlineSelectTab6 :6tabn
noremap <silent> <Plug>AirlineSelectTab5 :5tabn
noremap <silent> <Plug>AirlineSelectTab4 :4tabn
noremap <silent> <Plug>AirlineSelectTab3 :3tabn
noremap <silent> <Plug>AirlineSelectTab2 :2tabn
noremap <silent> <Plug>AirlineSelectTab1 :1tabn
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
vmap <C-_>9 <Plug>TComment_9
nmap <C-_>9 <Plug>TComment_9
omap <C-_>9 <Plug>TComment_9
vmap <C-_>8 <Plug>TComment_8
nmap <C-_>8 <Plug>TComment_8
omap <C-_>8 <Plug>TComment_8
vmap <C-_>7 <Plug>TComment_7
nmap <C-_>7 <Plug>TComment_7
omap <C-_>7 <Plug>TComment_7
vmap <C-_>6 <Plug>TComment_6
nmap <C-_>6 <Plug>TComment_6
omap <C-_>6 <Plug>TComment_6
vmap <C-_>5 <Plug>TComment_5
nmap <C-_>5 <Plug>TComment_5
omap <C-_>5 <Plug>TComment_5
vmap <C-_>4 <Plug>TComment_4
nmap <C-_>4 <Plug>TComment_4
omap <C-_>4 <Plug>TComment_4
vmap <C-_>3 <Plug>TComment_3
nmap <C-_>3 <Plug>TComment_3
omap <C-_>3 <Plug>TComment_3
vmap <C-_>2 <Plug>TComment_2
nmap <C-_>2 <Plug>TComment_2
omap <C-_>2 <Plug>TComment_2
vmap <C-_>1 <Plug>TComment_1
nmap <C-_>1 <Plug>TComment_1
omap <C-_>1 <Plug>TComment_1
map <C-_>ca <Plug>TComment_ca
map <C-_>cc <Plug>TComment_cc
map <C-_>s <Plug>TComment_s
map <C-_>n <Plug>TComment_n
map <C-_>a <Plug>TComment_a
map <C-_>b <Plug>TComment_b
map <C-_>i <Plug>TComment_i
map <C-_>r <Plug>TComment_r
map <C-_>  <Plug>TComment_ 
map <C-_>p <Plug>TComment_p
vmap <C-_><C-_> <Plug>TComment_
nmap <C-_><C-_> <Plug>TComment_
omap <C-_><C-_> <Plug>TComment_
nnoremap <silent> <Plug>TComment_gc9c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc9cg@
nnoremap <silent> <Plug>TComment_gc8c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc8cg@
nnoremap <silent> <Plug>TComment_gc7c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc7cg@
nnoremap <silent> <Plug>TComment_gc6c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc6cg@
nnoremap <silent> <Plug>TComment_gc5c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc5cg@
nnoremap <silent> <Plug>TComment_gc4c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc4cg@
nnoremap <silent> <Plug>TComment_gc3c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc3cg@
nnoremap <silent> <Plug>TComment_gc2c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc2cg@
nnoremap <silent> <Plug>TComment_gc1c :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gc1cg@
vnoremap <Plug>TComment_<C-_>9 :call tcomment#SetOption("count", 9)
vnoremap <Plug>TComment_9 :call tcomment#SetOption("count", 9)
nnoremap <Plug>TComment_<C-_>9 :call tcomment#SetOption("count", 9)
onoremap <Plug>TComment_<C-_>9 :call tcomment#SetOption("count", 9)
nnoremap <Plug>TComment_9 :call tcomment#SetOption("count", 9)
onoremap <Plug>TComment_9 :call tcomment#SetOption("count", 9)
vnoremap <Plug>TComment_<C-_>8 :call tcomment#SetOption("count", 8)
vnoremap <Plug>TComment_8 :call tcomment#SetOption("count", 8)
nnoremap <Plug>TComment_<C-_>8 :call tcomment#SetOption("count", 8)
onoremap <Plug>TComment_<C-_>8 :call tcomment#SetOption("count", 8)
nnoremap <Plug>TComment_8 :call tcomment#SetOption("count", 8)
onoremap <Plug>TComment_8 :call tcomment#SetOption("count", 8)
vnoremap <Plug>TComment_<C-_>7 :call tcomment#SetOption("count", 7)
vnoremap <Plug>TComment_7 :call tcomment#SetOption("count", 7)
nnoremap <Plug>TComment_<C-_>7 :call tcomment#SetOption("count", 7)
onoremap <Plug>TComment_<C-_>7 :call tcomment#SetOption("count", 7)
nnoremap <Plug>TComment_7 :call tcomment#SetOption("count", 7)
onoremap <Plug>TComment_7 :call tcomment#SetOption("count", 7)
vnoremap <Plug>TComment_<C-_>6 :call tcomment#SetOption("count", 6)
vnoremap <Plug>TComment_6 :call tcomment#SetOption("count", 6)
nnoremap <Plug>TComment_<C-_>6 :call tcomment#SetOption("count", 6)
onoremap <Plug>TComment_<C-_>6 :call tcomment#SetOption("count", 6)
nnoremap <Plug>TComment_6 :call tcomment#SetOption("count", 6)
onoremap <Plug>TComment_6 :call tcomment#SetOption("count", 6)
vnoremap <Plug>TComment_<C-_>5 :call tcomment#SetOption("count", 5)
vnoremap <Plug>TComment_5 :call tcomment#SetOption("count", 5)
nnoremap <Plug>TComment_<C-_>5 :call tcomment#SetOption("count", 5)
onoremap <Plug>TComment_<C-_>5 :call tcomment#SetOption("count", 5)
nnoremap <Plug>TComment_5 :call tcomment#SetOption("count", 5)
onoremap <Plug>TComment_5 :call tcomment#SetOption("count", 5)
vnoremap <Plug>TComment_<C-_>4 :call tcomment#SetOption("count", 4)
vnoremap <Plug>TComment_4 :call tcomment#SetOption("count", 4)
nnoremap <Plug>TComment_<C-_>4 :call tcomment#SetOption("count", 4)
onoremap <Plug>TComment_<C-_>4 :call tcomment#SetOption("count", 4)
nnoremap <Plug>TComment_4 :call tcomment#SetOption("count", 4)
onoremap <Plug>TComment_4 :call tcomment#SetOption("count", 4)
vnoremap <Plug>TComment_<C-_>3 :call tcomment#SetOption("count", 3)
vnoremap <Plug>TComment_3 :call tcomment#SetOption("count", 3)
nnoremap <Plug>TComment_<C-_>3 :call tcomment#SetOption("count", 3)
onoremap <Plug>TComment_<C-_>3 :call tcomment#SetOption("count", 3)
nnoremap <Plug>TComment_3 :call tcomment#SetOption("count", 3)
onoremap <Plug>TComment_3 :call tcomment#SetOption("count", 3)
vnoremap <Plug>TComment_<C-_>2 :call tcomment#SetOption("count", 2)
vnoremap <Plug>TComment_2 :call tcomment#SetOption("count", 2)
nnoremap <Plug>TComment_<C-_>2 :call tcomment#SetOption("count", 2)
onoremap <Plug>TComment_<C-_>2 :call tcomment#SetOption("count", 2)
nnoremap <Plug>TComment_2 :call tcomment#SetOption("count", 2)
onoremap <Plug>TComment_2 :call tcomment#SetOption("count", 2)
vnoremap <Plug>TComment_<C-_>1 :call tcomment#SetOption("count", 1)
vnoremap <Plug>TComment_1 :call tcomment#SetOption("count", 1)
nnoremap <Plug>TComment_<C-_>1 :call tcomment#SetOption("count", 1)
onoremap <Plug>TComment_<C-_>1 :call tcomment#SetOption("count", 1)
nnoremap <Plug>TComment_1 :call tcomment#SetOption("count", 1)
onoremap <Plug>TComment_1 :call tcomment#SetOption("count", 1)
nnoremap <silent> <Plug>TComment_gc :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gcg@
xnoremap <Plug>TComment_gc :TCommentMaybeInline
nnoremap <silent> <Plug>TComment_gcb :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gcbg@
nnoremap <silent> <Plug>TComment_gcc :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_gccg@$
noremap <Plug>TComment_ic :call tcomment#TextObjectInlineComment()
xnoremap <silent> <Plug>TComment_Comment :if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | '<,'>TCommentMaybeInline!
nnoremap <silent> <Plug>TComment_Commentb :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_Commentbg@
nnoremap <silent> <Plug>TComment_Commentc :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_Commentcg@$
nnoremap <silent> <Plug>TComment_Comment :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_Commentg@
xnoremap <silent> <Plug>TComment_Uncomment :if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | call tcomment#SetOption("mode_extra", "U") | '<,'>TCommentMaybeInline
nnoremap <silent> <Plug>TComment_Uncommentb :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_Uncommentbg@
nnoremap <silent> <Plug>TComment_Uncommentc :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_Uncommentcg@$
nnoremap <silent> <Plug>TComment_Uncomment :call tcomment#ResetOption() | if v:count > 0 | call tcomment#SetOption("count", v:count) | endif | let w:tcommentPos = getpos(".") |set opfunc=TCommentOpFunc_Uncommentg@
noremap <Plug>TComment_\_s :TCommentAs =&ft_
noremap <Plug>TComment_\_n :TCommentAs =&ft 
noremap <Plug>TComment_\_a :TCommentAs 
noremap <Plug>TComment_\_b :TCommentBlock
noremap <Plug>TComment_\_r :TCommentRight
xnoremap <Plug>TComment_\_i :TCommentInline
noremap <Plug>TComment_\_  :TComment 
noremap <Plug>TComment_\_p vip:TComment
xnoremap <Plug>TComment_\__ :TCommentMaybeInline
nnoremap <Plug>TComment_\__ :TComment
snoremap <Plug>TComment_\__ :TComment
onoremap <Plug>TComment_\__ :TComment
noremap <Plug>TComment_<C-_>ca :call tcomment#SetOption("as", input("Comment as: ", &filetype, "customlist,tcomment#Complete"))
noremap <Plug>TComment_ca :call tcomment#SetOption("as", input("Comment as: ", &filetype, "customlist,tcomment#Complete"))
noremap <Plug>TComment_<C-_>cc :call tcomment#SetOption("count", v:count1)
noremap <Plug>TComment_cc :call tcomment#SetOption("count", v:count1)
noremap <Plug>TComment_<C-_>s :TCommentAs =&ft_
noremap <Plug>TComment_s :TCommentAs =&ft_
noremap <Plug>TComment_<C-_>n :TCommentAs =&ft 
noremap <Plug>TComment_n :TCommentAs =&ft 
noremap <Plug>TComment_<C-_>a :TCommentAs 
noremap <Plug>TComment_a :TCommentAs 
noremap <Plug>TComment_<C-_>b :TCommentBlock
noremap <Plug>TComment_b :TCommentBlock
noremap <Plug>TComment_<C-_>i v:TCommentInline mode=I#
noremap <Plug>TComment_i v:TCommentInline mode=I#
noremap <Plug>TComment_<C-_>r :TCommentRight
noremap <Plug>TComment_r :TCommentRight
noremap <Plug>TComment_<C-_>  :TComment 
noremap <Plug>TComment_  :TComment 
noremap <Plug>TComment_<C-_>p m`vip:TComment``
noremap <Plug>TComment_p m`vip:TComment``
vnoremap <Plug>TComment_<C-_><C-_> :TCommentMaybeInline
vnoremap <Plug>TComment_ :TCommentMaybeInline
nnoremap <Plug>TComment_<C-_><C-_> :TComment
onoremap <Plug>TComment_<C-_><C-_> :TComment
nnoremap <Plug>TComment_ :TComment
onoremap <Plug>TComment_ :TComment
vmap <C-Y>c <Plug>(emmet-code-pretty)
vnoremap <Plug>(emmet-code-pretty) :call emmet#codePretty()
nmap <C-Y>m <Plug>(emmet-merge-lines)
nnoremap <Plug>(emmet-merge-lines) :call emmet#mergeLines()
nmap <C-Y>A <Plug>(emmet-anchorize-summary)
nnoremap <Plug>(emmet-anchorize-summary) :call emmet#anchorizeURL(1)
nmap <C-Y>a <Plug>(emmet-anchorize-url)
nnoremap <Plug>(emmet-anchorize-url) :call emmet#anchorizeURL(0)
nmap <C-Y>k <Plug>(emmet-remove-tag)
nnoremap <Plug>(emmet-remove-tag) :call emmet#removeTag()
nmap <C-Y>j <Plug>(emmet-split-join-tag)
nnoremap <Plug>(emmet-split-join-tag) :call emmet#splitJoinTag()
nmap <C-Y>/ <Plug>(emmet-toggle-comment)
nnoremap <Plug>(emmet-toggle-comment) :call emmet#toggleComment()
nmap <C-Y>I <Plug>(emmet-image-encode)
nnoremap <Plug>(emmet-image-encode) :call emmet#imageEncode()
nmap <C-Y>i <Plug>(emmet-image-size)
nnoremap <Plug>(emmet-image-size) :call emmet#imageSize()
nnoremap <Plug>(emmet-move-prev-item) :call emmet#moveNextPrevItem(1)
nnoremap <Plug>(emmet-move-next-item) :call emmet#moveNextPrevItem(0)
nmap <C-Y>N <Plug>(emmet-move-prev)
nnoremap <Plug>(emmet-move-prev) :call emmet#moveNextPrev(1)
nmap <C-Y>n <Plug>(emmet-move-next)
nnoremap <Plug>(emmet-move-next) :call emmet#moveNextPrev(0)
vmap <C-Y>D <Plug>(emmet-balance-tag-outword)
vnoremap <Plug>(emmet-balance-tag-outword) :call emmet#balanceTag(-1)
nmap <C-Y>D <Plug>(emmet-balance-tag-outword)
nnoremap <Plug>(emmet-balance-tag-outword) :call emmet#balanceTag(-1)
vmap <C-Y>d <Plug>(emmet-balance-tag-inward)
vnoremap <Plug>(emmet-balance-tag-inward) :call emmet#balanceTag(1)
nmap <C-Y>d <Plug>(emmet-balance-tag-inward)
nnoremap <Plug>(emmet-balance-tag-inward) :call emmet#balanceTag(1)
nmap <C-Y>u <Plug>(emmet-update-tag)
nnoremap <Plug>(emmet-update-tag) :call emmet#updateTag()
nmap <C-Y>; <Plug>(emmet-expand-word)
nnoremap <Plug>(emmet-expand-word) :call emmet#expandAbbr(1,"")
vmap <C-Y>, <Plug>(emmet-expand-abbr)
vnoremap <Plug>(emmet-expand-abbr) :call emmet#expandAbbr(2,"")
nmap <C-Y>, <Plug>(emmet-expand-abbr)
nnoremap <Plug>(emmet-expand-abbr) :call emmet#expandAbbr(3,"")
snoremap <C-R> "_c
snoremap <silent> <C-H> c
snoremap <silent> <Del> c
snoremap <silent> <BS> c
snoremap <silent> <C-Tab> :call UltiSnips#ListSnippets()
map <F12> :!ctags -R --sort=yes --c-kinds=+p --fields=+iaS --extra=+q .
map <F9> :call TranslateWord()
map <C-F7> :emenu Encoding.End_line_format.	
map <S-F7> :emenu Encoding.Write.	
map <F7> :emenu Encoding.Read.	
nmap <F11> :call {MyUpdateCtagsFunction}()
vmap <silent> <C-F> a:call MyKeyMapHighlight()gv
nmap <silent> <C-F> a:call MyKeyMapHighlight()
nmap <PageDown> 
nmap <PageUp> 
vmap <F5> :q
nmap <F5> :q
map <F4> [I:let nr = input("Which one: ")|exe "normal " . nr ."[\t"
vmap <F3> :nohlsearchgv
nmap <F3> :nohlsearch
vmap <F2> :TagbarToggle
nmap <F2> :TagbarToggle
omap <F2> :TagbarToggle
vmap <F1> :WMToggle
nmap <F1> :WMToggle
omap <F1> :WMToggle
nmap <C-L> 5l
nmap <C-K> 5k
nmap <C-J> 5j
nmap <C-H> 5h
imap <silent>  X:call MyKeyMapHighlight()a
cmap <silent>  
inoremap <silent> 	 =UltiSnips#ExpandSnippet()
cmap <NL> <Left>
imap <NL> <Left>
cmap  <Right>
imap  <Right>
cmap  <Del>
imap  <Del>
imap m <Plug>(emmet-merge-lines)
imap A <Plug>(emmet-anchorize-summary)
imap a <Plug>(emmet-anchorize-url)
imap k <Plug>(emmet-remove-tag)
imap j <Plug>(emmet-split-join-tag)
imap / <Plug>(emmet-toggle-comment)
imap I <Plug>(emmet-image-encode)
imap i <Plug>(emmet-image-size)
imap N <Plug>(emmet-move-prev)
imap n <Plug>(emmet-move-next)
imap D <Plug>(emmet-balance-tag-outword)
imap d <Plug>(emmet-balance-tag-inward)
imap u <Plug>(emmet-update-tag)
imap ; <Plug>(emmet-expand-word)
imap , <Plug>(emmet-expand-abbr)
inoremap <silent> OC <Right>
imap 9 <Plug>TComment_9
imap 8 <Plug>TComment_8
imap 7 <Plug>TComment_7
imap 6 <Plug>TComment_6
imap 5 <Plug>TComment_5
imap 4 <Plug>TComment_4
imap 3 <Plug>TComment_3
imap 2 <Plug>TComment_2
imap 1 <Plug>TComment_1
imap s <Plug>TComment_s
imap n <Plug>TComment_n
imap a <Plug>TComment_a
imap b <Plug>TComment_b
imap i <Plug>TComment_i
imap r <Plug>TComment_r
imap   <Plug>TComment_ 
imap p <Plug>TComment_p
imap  <Plug>TComment_
inoremap <silent> { {}O
let &cpo=s:cpo_save
unlet s:cpo_save
set keymap=ukrainian-jcuken
set autoindent
set background=dark
set backspace=indent,eol,start
set balloonexpr=<SNR>40_ErrorMessageBalloons()
set completeopt=menuone,longest,preview
set errorformat=%f:%l:%c:\ %t%*[^:]:%m,%f:%l:\ %t%*[^:]:%m,%*[^\"]\"%f\"%*\\D%l:\ %m,\"%f\"%*\\D%l:\ %m,%-G%f:%l:\ (Each\ undeclared\ identifier\ is\ reported\ only\ once,%-G%f:%l:\ for\ each\ function\ it\ appears\ in.),%-GIn\ file\ included\ from\ %f:%l:%c:,%-GIn\ file\ included\ from\ %f:%l:%c\\,,%-GIn\ file\ included\ from\ %f:%l:%c,%-GIn\ file\ included\ from\ %f:%l,%-G%*[\ ]from\ %f:%l:%c,%-G%*[\ ]from\ %f:%l:,%-G%*[\ ]from\ %f:%l\\,,%-G%*[\ ]from\ %f:%l,%f:%l:%c:%m,%f(%l):%m,%f:%l:%m,\"%f\"\\,\ line\ %l%*\\D%c%*[^\ ]\ %m,%D%*\\a[%*\\d]:\ Entering\ directory\ %*[`']%f',%X%*\\a[%*\\d]:\ Leaving\ directory\ %*[`']%f',%D%*\\a:\ Entering\ directory\ %*[`']%f',%X%*\\a:\ Leaving\ directory\ %*[`']%f',%DMaking\ %*\\a\ in\ %f,%f|%l|\ %m
set fileencodings=utf-8,cp1251,koi8-r,cp866
set guitablabel=%!MyGuiTabLabel()
set helplang=uk
set hlsearch
set ignorecase
set imsearch=0
set incsearch
set laststatus=2
set nomodeline
set mouse=a
set omnifunc=xolox#lua#omnifunc
set printoptions=paper:a4
set pumheight=20
set ruler
set shiftwidth=4
set showcmd
set showtabline=2
set smartindent
set spelllang=
set statusline=%<%f%h%m%r%=format=%{&fileformat}\ file=%{&fileencoding}\ enc=%{&encoding}\ %b\ 0x%B\ %l,%c%V\ %P
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set noswapfile
set tabline=%!airline#extensions#tabline#get()
set tabstop=4
set tags=./tags,./TAGS,tags,TAGS,~/.vimtags
set visualbell
set wildcharm=<Tab>
set wildmenu
set winminheight=0
set winminwidth=0
set nowrapscan
" vim: set ft=vim :
