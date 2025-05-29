typedef struct _IShellLinkW IShellLinkW;

typedef struct _SHITEMID
{
	USHORT cb;
	BYTE abID[1];
} 	SHITEMID;
typedef struct _ITEMIDLIST
{
	SHITEMID mkid;
} 	ITEMIDLIST;

#define PIDLIST_ABSOLUTE         LPITEMIDLIST
#define PCIDLIST_ABSOLUTE        LPCITEMIDLIST
typedef /* [wire_marshal] */ const ITEMIDLIST __unaligned* LPCITEMIDLIST;
typedef /* [wire_marshal] */ ITEMIDLIST __unaligned* LPITEMIDLIST;

typedef struct IShellLinkWVtbl
{
	BEGIN_INTERFACE

		HRESULT(STDMETHODCALLTYPE* QueryInterface)(
			__RPC__in IShellLinkW* This,
			/* [in] */ __RPC__in REFIID riid,
			/* [annotation][iid_is][out] */
			_COM_Outptr_  void** ppvObject);

	ULONG(STDMETHODCALLTYPE* AddRef)(
		__RPC__in IShellLinkW* This);

	ULONG(STDMETHODCALLTYPE* Release)(
		__RPC__in IShellLinkW* This);

	HRESULT(STDMETHODCALLTYPE* GetPath)(
		__RPC__in IShellLinkW* This,
		/* [size_is][string][out] */ __RPC__out_ecount_full_string(cch) LPWSTR pszFile,
		/* [in] */ int cch,
		/* [unique][out][in] */ __RPC__inout_opt WIN32_FIND_DATAW* pfd,
		/* [in] */ DWORD fFlags);

	HRESULT(STDMETHODCALLTYPE* GetIDList)(
		__RPC__in IShellLinkW* This,
		/* [out] */ __RPC__deref_out_opt PIDLIST_ABSOLUTE* ppidl);

	HRESULT(STDMETHODCALLTYPE* SetIDList)(
		__RPC__in IShellLinkW* This,
		/* [unique][in] */ __RPC__in_opt PCIDLIST_ABSOLUTE pidl);

	HRESULT(STDMETHODCALLTYPE* GetDescription)(
		__RPC__in IShellLinkW* This,
		/* [size_is][string][out] */ __RPC__out_ecount_full_string(cch) LPWSTR pszName,
		int cch);

	HRESULT(STDMETHODCALLTYPE* SetDescription)(
		__RPC__in IShellLinkW* This,
		/* [string][in] */ __RPC__in_string LPCWSTR pszName);

	HRESULT(STDMETHODCALLTYPE* GetWorkingDirectory)(
		__RPC__in IShellLinkW* This,
		/* [size_is][string][out] */ __RPC__out_ecount_full_string(cch) LPWSTR pszDir,
		int cch);

	HRESULT(STDMETHODCALLTYPE* SetWorkingDirectory)(
		__RPC__in IShellLinkW* This,
		/* [string][in] */ __RPC__in_string LPCWSTR pszDir);

	HRESULT(STDMETHODCALLTYPE* GetArguments)(
		__RPC__in IShellLinkW* This,
		/* [size_is][string][out] */ __RPC__out_ecount_full_string(cch) LPWSTR pszArgs,
		/* [in] */ int cch);

	HRESULT(STDMETHODCALLTYPE* SetArguments)(
		__RPC__in IShellLinkW* This,
		/* [string][in] */ __RPC__in_string LPCWSTR pszArgs);

	HRESULT(STDMETHODCALLTYPE* GetHotkey)(
		__RPC__in IShellLinkW* This,
		/* [out] */ __RPC__out WORD* pwHotkey);

	HRESULT(STDMETHODCALLTYPE* SetHotkey)(
		__RPC__in IShellLinkW* This,
		/* [in] */ WORD wHotkey);

	HRESULT(STDMETHODCALLTYPE* GetShowCmd)(
		__RPC__in IShellLinkW* This,
		/* [out] */ __RPC__out int* piShowCmd);

	HRESULT(STDMETHODCALLTYPE* SetShowCmd)(
		__RPC__in IShellLinkW* This,
		/* [in] */ int iShowCmd);

	HRESULT(STDMETHODCALLTYPE* GetIconLocation)(
		__RPC__in IShellLinkW* This,
		/* [size_is][string][out] */ __RPC__out_ecount_full_string(cch) LPWSTR pszIconPath,
		/* [in] */ int cch,
		/* [out] */ __RPC__out int* piIcon);

	HRESULT(STDMETHODCALLTYPE* SetIconLocation)(
		__RPC__in IShellLinkW* This,
		/* [string][in] */ __RPC__in_string LPCWSTR pszIconPath,
		/* [in] */ int iIcon);

	HRESULT(STDMETHODCALLTYPE* SetRelativePath)(
		__RPC__in IShellLinkW* This,
		/* [string][in] */ __RPC__in_string LPCWSTR pszPathRel,
		/* [in] */ DWORD dwReserved);

	HRESULT(STDMETHODCALLTYPE* Resolve)(
		__RPC__in IShellLinkW* This,
		/* [unique][in] */ __RPC__in_opt HWND hwnd,
		/* [in] */ DWORD fFlags);

	HRESULT(STDMETHODCALLTYPE* SetPath)(
		__RPC__in IShellLinkW* This,
		/* [string][in] */ __RPC__in_string LPCWSTR pszFile);

	END_INTERFACE
} IShellLinkWVtbl;

typedef struct _IShellLinkW
{
	struct IShellLinkWVtbl* lpVtbl;
}IShellLinkW;