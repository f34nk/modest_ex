defmodule ModestEx.MixProject do
  use Mix.Project

  def project do
    [
      app: :modest_ex,
      version: "2.0.0",
      elixir: "~> 1.5",
      compilers: Mix.compilers(),
      build_embedded: Mix.env() == :prod,
      start_permanent: Mix.env() == :prod,
      name: "ModestEx",
      description: """
        ModestEx - A library to do pipeable transformations on html strings with CSS selectors, e.g. find(), prepend(), append(), replace() etc.
      """,
      docs: docs(),
      deps: deps(),
      package: package()
    ]
  end

  defp docs do
    [
      main: "ModestEx"
    ]
  end

  def package do
    [
      maintainers: ["Frank Eickhoff"],
      licenses: ["GNU LGPL"],
      links: %{
        "Github" => "https://github.com/f34nk/modest_ex",
        "Issues" => "https://github.com/f34nk/modest_ex/issues",
        "lexbor_erl" => "https://github.com/f34nk/lexbor_erl",
        "lexbor" => "https://github.com/lexbor/lexbor"
      },
      files: [
        "lib",
        "test",
        "mix.exs",
        "README.md",
        "LICENSE"
      ]
    ]
  end

  def application do
    [
      extra_applications: [:logger, :lexbor_erl],
      env: [
        scope: :body_children
      ]
    ]
  end

  defp deps do
    [
      # documentation helpers
      {:ex_doc, "~> 0.31", only: :dev, runtime: false},
      # HTML parsing and manipulation
      {:lexbor_erl, "~> 0.3.0"}
    ]
  end
end
