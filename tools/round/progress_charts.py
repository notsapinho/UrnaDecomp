"""The progress history and the README's charts, for status.py.

    splat/history.tsv                              one row per point at which the matches changed, oldest first
    docs/img/progress-history-{light,dark}.svg     the share of functions matched over time: all of them, TSE code
    docs/img/progress-components-{light,dark}.svg  the share of functions matched per component, by origin

`make -C src status` (status.py) appends a row to splat/history.tsv when the totals of splat/scan.tsv differ from its
last row, dated when it runs, and redraws the charts from the two files. `status.py --check` fails when the last row
is not the scan's totals or a chart is not what the two files draw. The rows before the first commit of this file were
summed from the matches at every earlier point of main's history, each by the scan of that commit.
"""
import datetime
import os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
HISTORY = os.path.join(ROOT, 'splat', 'history.tsv')
IMG = os.path.join(ROOT, 'docs', 'img')
COLUMNS = ['date', 'matches', 'functions', 'code_bytes', 'code_total',
           'tse_matches', 'tse_functions', 'tse_code_bytes', 'tse_code_total']

FONT = "system-ui, -apple-system, 'Segoe UI', Helvetica, Arial, sans-serif"
MONO = "ui-monospace, SFMono-Regular, Menlo, Consolas, monospace"
# The light and dark steps of one palette (validated against GitHub's #ffffff and #0d1117 surfaces).
THEMES = {
    'light': {'primary': '#0b0b0b', 'secondary': '#52514e', 'muted': '#898781', 'grid': '#e1e0d9',
              'baseline': '#c3c2b7', 'surface': '#ffffff', 'all': '#2a78d6', 'tse': '#eb6834', 'track': '#cde2fb'},
    'dark': {'primary': '#f0efec', 'secondary': '#c3c2b7', 'muted': '#898781', 'grid': '#2c2c2a',
             'baseline': '#383835', 'surface': '#0d1117', 'all': '#3987e5', 'tse': '#d95926', 'track': '#16304f'},
}
MONTHS = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']


def point(rows, tse):
    """The totals of a scan: matches and functions, matched and total code bytes, for all and for TSE code."""
    p = [0] * 8
    for r in rows:
        for base in (0, 4) if r['group'] in tse else (0,):
            p[base + 1] += 1
            p[base + 3] += r['size']
            if r['verdict'] == 'match':
                p[base] += 1
                p[base + 2] += r['size']
    return p


def read_history(path=HISTORY):
    with open(path, encoding='utf-8') as f:
        header = f.readline().rstrip('\n').split('\t')
        if header != COLUMNS:
            raise SystemExit(f'{os.path.relpath(path, ROOT)}: the header is not {" ".join(COLUMNS)}')
        out = []
        for line in f:
            if line.strip():
                f_ = line.rstrip('\n').split('\t')
                out.append((f_[0], [int(x) for x in f_[1:]]))
    return out


def history_text(history):
    lines = ['\t'.join(COLUMNS)] + ['\t'.join([d] + [str(x) for x in p]) for d, p in history]
    return '\n'.join(lines) + '\n'


def now():
    return datetime.datetime.now(datetime.timezone.utc).replace(microsecond=0).strftime('%Y-%m-%dT%H:%M:%SZ')


def esc(s):
    return s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')


def f1(x):
    s = f'{x:.1f}'
    return s[:-2] if s.endswith('.0') else s


def n(x):
    return f'{x:,}'


def pct(a, b):
    return f'{100 * a / b:.1f}%' if b else '0.0%'


def parse(date):
    return datetime.datetime.strptime(date, '%Y-%m-%dT%H:%M:%SZ').replace(tzinfo=datetime.timezone.utc)


def svg(width, height, body, label):
    return (f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
            f'viewBox="0 0 {width} {height}" role="img" aria-label="{esc(label)}" font-family="{FONT}">\n'
            f'<title>{esc(label)}</title>\n{body}</svg>\n')


def text(x, y, s, fill, size=12, anchor='start', weight=None, family=None, extra=''):
    w = f' font-weight="{weight}"' if weight else ''
    fam = f' font-family="{family}"' if family else ''
    a = f' text-anchor="{anchor}"' if anchor != 'start' else ''
    return f'<text x="{f1(x)}" y="{f1(y)}" font-size="{size}" fill="{fill}"{a}{w}{fam}{extra}>{esc(s)}</text>\n'


def ticks(start, end):
    """Midnight-UTC ticks between two datetimes, at most eight, at a round step of days."""
    span = (end - start).total_seconds() / 86400
    step = next((d for d in (1, 2, 3, 7, 14, 30, 61, 91, 182, 365) if span / d <= 7), 730)
    day = datetime.datetime(start.year, start.month, start.day, tzinfo=datetime.timezone.utc)
    if day < start:
        day += datetime.timedelta(days=1)
    out = []
    while day <= end:
        out.append(day)
        day += datetime.timedelta(days=step)
    return out


def history_chart(history, theme):
    t = THEMES[theme]
    W, H = 800, 300
    L, R, T, B = 44, 168, 64, 34
    pw, ph = W - L - R, H - T - B
    first, last = parse(history[0][0]), parse(history[-1][0])
    if (last - first).total_seconds() < 86400:
        last = first + datetime.timedelta(days=1)
    span = (last - first).total_seconds()
    x = lambda d: L + pw * (d - first).total_seconds() / span
    y = lambda v: T + ph * (1 - v)
    series = [('all', 'All functions', 0, 1), ('tse', 'TSE code', 4, 5)]
    b = text(0, 18, 'Functions matched over time', t['primary'], size=15, weight='600')
    lx = 0
    for key, name, _, _ in series:
        b += (f'<line x1="{lx}" y1="40" x2="{lx + 16}" y2="40" stroke="{t[key]}" stroke-width="2" '
              f'stroke-linecap="round"/>\n')
        b += text(lx + 22, 44, name, t['secondary'])
        lx += 22 + 7 * len(name) + 20
    for v in (0, 0.25, 0.5, 0.75, 1):
        b += (f'<line x1="{L}" y1="{f1(y(v))}" x2="{L + pw}" y2="{f1(y(v))}" '
              f'stroke="{t["baseline"] if v == 0 else t["grid"]}" stroke-width="1"/>\n')
        b += text(L - 8, y(v) + 4, f'{int(v * 100)}%', t['muted'], size=11, anchor='end')
    for d in ticks(first, last):
        label = f'{MONTHS[d.month - 1]} {d.day}' + (f', {d.year}' if (last - first).days > 300 else '')
        b += text(x(d), H - B + 18, label, t['muted'], size=11, anchor='middle')
    ends = []
    for key, name, a, c in series:
        pts = [(x(parse(d)), y(p[a] / p[c] if p[c] else 0)) for d, p in history]
        path = f'M{f1(pts[0][0])} {f1(pts[0][1])}'
        for (x0, y0), (x1, y1) in zip(pts, pts[1:]):
            path += f' H{f1(x1)} V{f1(y1)}'
        if pts[-1][0] < L + pw:
            path += f' H{f1(L + pw)}'
        b += (f'<path d="{path}" fill="none" stroke="{t[key]}" stroke-width="2" stroke-linejoin="round" '
              f'stroke-linecap="round"/>\n')
        b += (f'<circle cx="{f1(L + pw)}" cy="{f1(pts[-1][1])}" r="4" fill="{t[key]}" stroke="{t["surface"]}" '
              f'stroke-width="2"/>\n')
        p = history[-1][1]
        ends.append([pts[-1][1], pct(p[a], p[c]), f'{n(p[a])} / {n(p[c])}'])
    ends.sort()
    for i in range(1, len(ends)):
        ends[i][0] = max(ends[i][0], ends[i - 1][0] + 30)
    for ey, share, count in ends:
        b += text(L + pw + 12, ey + 1, share, t['primary'], size=13, weight='600')
        b += text(L + pw + 12, ey + 15, count, t['secondary'], size=11)
    return svg(W, H, b, 'Functions matched over time: all functions and TSE code')


def components_chart(groups, theme):
    """groups: [(origin, [(component, matched, total), ...]), ...]"""
    t = THEMES[theme]
    W = 800
    NAME, BAR, BW, ROW, HEAD = 0, 128, 480, 22, 34
    rows = sum(len(c) for _, c in groups)
    H = 36 + HEAD * len(groups) + ROW * rows + 4
    b = text(0, 18, 'Functions matched by component', t['primary'], size=15, weight='600')
    yy = 36
    for origin, comps in groups:
        m, tot = sum(c[1] for c in comps), sum(c[2] for c in comps)
        yy += HEAD
        b += text(NAME, yy - 10, origin, t['primary'], size=13, weight='600')
        b += text(BAR + BW, yy - 10, f'{n(m)} / {n(tot)} · {pct(m, tot)}', t['secondary'], size=12, anchor='end')
        for name, m, tot in comps:
            cy = yy + ROW / 2
            b += text(NAME, cy + 4, name, t['secondary'], size=12, family=MONO)
            b += (f'<rect x="{BAR}" y="{f1(cy - 6)}" width="{BW}" height="12" rx="3" fill="{t["track"]}"/>\n')
            w = BW * m / tot if tot else 0
            if w > 0:
                r = min(3, w / 2)
                b += (f'<path d="M{BAR} {f1(cy - 6)} H{f1(BAR + w - r)} a{f1(r)} {f1(r)} 0 0 1 {f1(r)} {f1(r)} '
                      f'V{f1(cy + 6 - r)} a{f1(r)} {f1(r)} 0 0 1 {f1(-r)} {f1(r)} H{BAR} Z" fill="{t["all"]}"/>\n')
            b += text(BAR + BW + 12, cy + 4, pct(m, tot), t['primary'], size=12, weight='600')
            b += text(BAR + BW + 64, cy + 4, f'{n(m)} / {n(tot)}', t['secondary'], size=12)
            yy += ROW
    return svg(W, H, b, 'Functions matched by component')


def charts(history, groups):
    """The chart files, as {path: text}."""
    out = {}
    for theme in THEMES:
        out[os.path.join(IMG, f'progress-history-{theme}.svg')] = history_chart(history, theme)
        out[os.path.join(IMG, f'progress-components-{theme}.svg')] = components_chart(groups, theme)
    return out
