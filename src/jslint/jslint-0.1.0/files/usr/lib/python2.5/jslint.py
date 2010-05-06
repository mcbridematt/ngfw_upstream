#! /usr/bin/python

import re, subprocess, sys

class Problem:
  IGNORED = [ re.compile(x) for x in
              [ """The body of a for in should be wrapped in an if""",
                """Use '[=!]==' to compare with""",
                """Expected an assignment or function call and instead saw an expression""",
                """Missing semicolon"""] ]

  def __init__(self, lineNumber, characterNumber, error, line):
    self.lineNumber = int(lineNumber)
    self.characterNumber = int(characterNumber)
    self.error = error
    self.line = line

  def isIgnored(self):
    for regex in self.IGNORED:
      if regex.search(self.error):
        return True
    return False

  def __repr__(self):
    s =  "** %04d:%03d -> %s" % (self.lineNumber, 
                              self.characterNumber,
                              self.error)
    s += "\n"
    s += "%s" % (self.line,)
    return s

class Problems:
  SEA_MONKEY = "/usr/bin/smjs"
  JS_LINT = "/usr/share/javascript/jslint.js"

  TAG_RE = re.compile(r'<.*?>')
  PARAGRAPH_RE = re.compile(r'(?<!^)<(p|div).*?>')
  WHITESPACE_RE = re.compile(r'&nbsp;')
  TERMINATION_RE = re.compile(r'Implied global:.*',
                              re.MULTILINE | re.DOTALL)
  PROBLEM_RE = re.compile(r'^Problem at line (\d+) character (\d+): ([^\n]+)\n(.+)', re.MULTILINE)

  def __init__(self, file):
    self.file = file
    self.data = self._runJsLint()
    self.allProblems = self._extractProblems()
    self.problems = [ pb for pb in self.allProblems
                      if not pb.isIgnored() ]

  def _runJsLint(self):
    return subprocess.Popen([self.SEA_MONKEY,
                             self.JS_LINT,
                             open(self.file).read()],
                            stdout = subprocess.PIPE).communicate()[0]

  def _extractProblems(self):
    d = self.PARAGRAPH_RE.sub('\n', self.data)
    d = self.WHITESPACE_RE.sub(' ', d)
    d = self.TAG_RE.sub('', d)
    d = self.TERMINATION_RE.sub('', d)
    return [ Problem(*tup) for tup in self.PROBLEM_RE.findall(d) ]

  def __repr__(self):
    s = "=== %s --> %d problem(s) ===" % (self.file, len(self.problems))
    s += "\n"
    for pb in self.problems:
      s += str(pb) + "\n"
    return s.strip()

if __name__ == '__main__':
  for file in sys.argv[1:]:
    print Problems(file)
