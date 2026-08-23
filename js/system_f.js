/* ========================================================
   system_f.js
   Gerencia a interface, navegação e preferências do usuário
   (Equivalente funcional do system_f.h para a Web)
   ======================================================== */

// Função para Alternar Abas
function showTab(tabId, trigger) {
    // Esconder todas as sections
    document.querySelectorAll('.tab-content').forEach(section => {
        section.classList.remove('active');
        section.hidden = true;
    });
    // Mostrar a selecionada
    const selectedSection = document.getElementById(tabId);
    selectedSection.classList.add('active');
    selectedSection.hidden = false;
    
    // Atualizar cor dos botões do menu
    document.querySelectorAll('.tab-btn').forEach(btn => {
        btn.classList.remove('active');
        btn.setAttribute('aria-selected', 'false');
        btn.tabIndex = -1;
    });
    
    // O Event.target ou busca direta pega o botão clicado
    const selectedButton = trigger || document.querySelector(`[aria-controls="${tabId}"]`);
    selectedButton.classList.add('active');
    selectedButton.setAttribute('aria-selected', 'true');
    selectedButton.tabIndex = 0;
}

// Função do Tema (Dark/Light)
function toggleTheme() {
    document.body.classList.toggle('light-theme');
    const isLight = document.body.classList.contains('light-theme');
    const ptText = isLight ? '🌙 Dark Mode' : '☀️ Light Mode';
    document.getElementById('theme-btn').innerText = ptText;
    document.getElementById('theme-btn').setAttribute('aria-pressed', String(isLight));
}

// Função do Idioma (Português/Inglês)
function toggleLang() {
    const isEn = document.body.classList.contains('lang-en');
    if (isEn) {
        document.body.classList.replace('lang-en', 'lang-pt');
        document.documentElement.lang = 'pt-BR';
        document.getElementById('lang-btn').innerText = '🇺🇸 English';
        document.getElementById('lang-btn').setAttribute('aria-pressed', 'false');
    } else {
        document.body.classList.replace('lang-pt', 'lang-en');
        document.documentElement.lang = 'en';
        document.getElementById('lang-btn').innerText = '🇧🇷 Português';
        document.getElementById('lang-btn').setAttribute('aria-pressed', 'true');
    }
}

function initializePreferences() {
    const isLight = window.matchMedia('(prefers-color-scheme: light)').matches;
    const isPortuguese = navigator.language.toLowerCase().startsWith('pt');

    document.body.classList.toggle('light-theme', isLight);
    document.body.classList.add(isPortuguese ? 'lang-pt' : 'lang-en');
    document.documentElement.lang = isPortuguese ? 'pt-BR' : 'en';

    const themeButton = document.getElementById('theme-btn');
    themeButton.innerText = isLight ? '🌙 Dark Mode' : '☀️ Light Mode';
    themeButton.setAttribute('aria-pressed', String(isLight));

    const languageButton = document.getElementById('lang-btn');
    languageButton.innerText = isPortuguese ? '🇺🇸 English' : '🇧🇷 Português';
    languageButton.setAttribute('aria-pressed', String(!isPortuguese));

    const tabs = Array.from(document.querySelectorAll('[role="tab"]'));
    tabs.forEach((tab, index) => {
        tab.addEventListener('keydown', event => {
            if (!['ArrowLeft', 'ArrowRight', 'Home', 'End'].includes(event.key)) return;
            event.preventDefault();
            let next = index;
            if (event.key === 'ArrowRight') next = (index + 1) % tabs.length;
            if (event.key === 'ArrowLeft') next = (index - 1 + tabs.length) % tabs.length;
            if (event.key === 'Home') next = 0;
            if (event.key === 'End') next = tabs.length - 1;
            tabs[next].focus();
            showTab(tabs[next].getAttribute('aria-controls'), tabs[next]);
        });
    });
}

document.addEventListener('DOMContentLoaded', initializePreferences);
