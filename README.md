# 메르센 소수 찾기 (C++ + JavaScript)

계산은 C++로 작성하고, Emscripten으로 WebAssembly로 빌드해 브라우저의 JavaScript 화면에서 호출하는 프로그램입니다. 별도 라이브러리 없이 C++17로 빌드합니다.

## 브라우저에서 실행하기

1. Emscripten SDK를 설치하고 활성화합니다 (`emsdk_env` 실행).
2. 저장소 루트에서 빌드합니다:

   ```sh
   em++ main.cpp -O2 -std=c++17 -s WASM=1 -s MODULARIZE=1 -s EXPORT_ES6=1 \
     -s EXPORTED_FUNCTIONS='["_find_mersenne_primes"]' \
     -s EXPORTED_RUNTIME_METHODS='["UTF8ToString"]' \
     -s ENVIRONMENT=web -o mersenne.js
   ```

3. 로컬 웹 서버로 저장소 루트를 열고 `index.html`에 접속합니다. 예: `python3 -m http.server 8000`
4. 페이지에서 지수 최댓값을 입력하고 **찾기 시작**을 누릅니다.

빌드하면 `mersenne.js`와 `mersenne.wasm`이 생성됩니다. 브라우저는 JS 모듈을 통해 C++ 함수를 호출하고 결과를 표시합니다. 파일을 직접 `file://`로 열지 말고 로컬 서버에서 실행하세요.

## C++ 콘솔에서 실행하기

```sh
g++ -O2 -std=c++17 main.cpp -o mersenne
./mersenne 31
```

## 범위와 판정법

뤼카–레머 판정법으로 소수 지수 `p`를 검사합니다. 이 예제는 표준 64비트 정수 연산에 맞춰 `2 ≤ p ≤ 61`을 지원합니다. 입력한 최댓값까지의 소수 지수를 검사합니다. 큰 지수까지 지원하려면 다중 정밀도 정수 구현이 필요합니다.
