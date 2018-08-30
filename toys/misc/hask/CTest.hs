module CTest where

import Foreign.C

hello :: IO CString
hello = newCString "hello"

foreign export ccall hello :: IO CString

