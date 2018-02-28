#!/bin/bash

current=`pwd`
test -d package_test || mkdir package_test
rm -rf package_test/*

mkdir package_test/modest_ex

mix hex.build
mv modest_ex-*.tar package_test/modest_ex

cd package_test/modest_ex
tar -xf *.tar
tar -xzf *.tar.gz

cd ..
rm -rf foo
mkdir foo
cd foo
cat > mix.exs <<EOF
defmodule Foo.MixProject do
  use Mix.Project

  def project() do
    [
      app: :foo,
      version: "1.0.0",
      package: [
        links: %{},
        licenses: ["Apache 2.0"],
        description: "test",
        maintainers: ["me"]
      ],
      deps: deps()
    ]
  end

  defp deps do
    [
      {:modest_ex, path: "../modest_ex"}
    ]
  end
end
EOF

mix deps.get
mix compile

mix run -e 'IO.inspect {:ok, "<a>Hello</a>"} = ModestEx.find("<p><a>Hello</a> World</p>", "p a")'

# cd $current
# rm -rf package_test

echo "ok"